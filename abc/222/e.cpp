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
  bool operator<=(const mint a) const { return mint(*this) <= a; }
  bool operator<(const mint a) const { return mint(*this) < a; }
  bool operator>=(const mint a) const { return mint(*this) >= a; }
  bool operator>(const mint a) const { return mint(*this) > a; }
  bool operator==(const mint a) const { return mint(*this) == a; }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

vector<set<pair<ll,ll>>> G; // G[u]:= (隣接する頂点v, 辺id)の集合

bool dfs(ll u, ll parent, ll t, vector<ll> &Ecnt) {
    if (u == t) return true;

    for(auto[v, eid]: G[u]) {
        if (v == parent) continue;
        bool res = dfs(v, u, t, Ecnt);
        if (res) {
            Ecnt[eid]++;
            return true;
        }
    }
    return false;
}


// dp[i][j] := i番目の辺まで見たとき、赤い道をj回通るときの場合の数
// のほうがわかりやすい。
void solve() {
    ll N, M, K; cin >> N >> M >> K;
    G.resize(N);
    vector<ll> A(M);
    for(ll i=0; i<M; i++) {
        cin >> A[i]; A[i]--;
    }
    for(ll i=0; i<N-1; i++) {
        ll u, v; cin >> u >> v; u--; v--;
        G[u].insert({v,i});
        G[v].insert({u,i});
    }

    // どの辺を何回通るのか数える
    // DFSをM回するので、O((N+N)M)
    vector<ll> Ecnt(N-1); // Ecnt[i] := 辺iを通る回数
    for(ll i=0; i<M-1; i++) {
        ll s=A[i], t=A[i+1];
        dfs(s, -1, t, Ecnt);
    }

    // 通る辺の合計値totalを求める
    ll total = 0;
    for(ll val: Ecnt) total += val;

    // dp[i] := 赤い道をi回通る場合の数。貰うDP。
    vector<mint> dp(total+1, 0);  // 高々NM
    dp[0] = 1;
    for(ll val: Ecnt) {
        for(ll i=total; i>=0; i--) {
            if (i+val > total) continue;
            dp[i+val] += dp[i];  // 赤色に塗る
        }
    }

    // R = K+B になる場合の数を数える
    // B = total - R より、 2R = K+total
    mint ans = 0;
    for(ll r=0; r<=total; r++) {
        if (2*r == K+total) ans += dp[r];
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}