#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

/** 自動でMODをとるModInt型
 *
 * Usage
 *   // 基本的な使い方
 *   mint a, b;
 *   a = 100;
 *   b = a + MOD;
 *   // istreamとostreamをオーバロードしてるので、mint型も普通に入出力できる
 *   cout << b << endl;  // 100
 *   // 明示的にlong long型を出力するときは.xを参照する
 *   cout << b.x << endl;  // 100
 *
 * References
 *  https://youtu.be/L8grWxBlIZ4?t=9858
 *  https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
 *  https://youtu.be/8uowVvQ_-Mo?t=1329 : division
 */
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

/**
 * @brief mintを使った高速なnCr計算
 *
 * @tparam T
 *
 * @details
 *  O(n)で前計算を構築し、nCrのクエリにO(1)で応答する
 *
 *  * 0!, 1!, ..., (n-1)!, n!
 *  * 1/n!, 1/(n-1)!, ..., 1/0!
 *  のテーブルをそれぞれO(n)で構築する。
 *
 *  それにより nCr = n!/(r!*(n-r)!) のクエリにO(1)で応答できる
 *
 * @usage
 *  combination_mint_builder<ll> c(1e6);
 *  mint ans = c(6,2);  // 6C2
 */
template <typename T>
struct combination_mint_builder {
    vector<mint> fact, ifact;
    combination_mint_builder(T n) {
        assert(n < MOD);
        fact.resize(n+1); ifact.resize(n+1);
        fact[0] = 1;
        for(T i=1; i<=n; i++) fact[i] = fact[i-1]*i;
        ifact[n] = fact[n].inv();
        for(T i=n; i>=1; i--) ifact[i-1] = ifact[i]*i;
    }
    mint operator()(T n, T r) {
        if (r<0 || r>n) return 0;
        return fact[n]*ifact[r]*ifact[n-r];
    }
};
combination_mint_builder<ll> c(1e6);


// dp[i][j][k] := 左からi番目まで見て、赤く塗った頂点の数がj個で、異なる色で塗られた頂点を結ぶ辺の本数(MOD 2)
// 👆間に合うわけ無いだろ！
// 頂点ごとに独立して考えられると嬉しい。頂点ごとの貢献度を考えられないか？
// 奇次数の頂点を偶数個赤く塗る解法
void solve() {
    ll N, M, K; cin >> N >> M >> K;
    vector<ll> d(N);  // 各頂点の次数の偶奇
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v; u--; v--;
        d[u] ^= 1;
        d[v] ^= 1;
    }

    // 次数が1の頂点と0の頂点を集計する
    ll one = 0, zero = 0;
    for(ll i=0; i<N; i++) {
        if (d[i]) one++;
        else zero++;
    }

    // 次数が奇数の頂点のうち、偶数個を赤く塗る
    mint ans = 0;
    for(ll i=0; i<=K; i+=2) {
        ans += c(one, i) * c(zero, K-i);
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}