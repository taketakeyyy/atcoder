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

void solve() {
    ll N, P; cin >> N >> P;
    mint p = mint(P)/100;
    mint q = mint(1)-p;

    vector<bool> visited(N+1);
    vector<mint> memo(N+1);
    // ラムダ式で再帰関数書くときは、自分自身の引数をとり、戻り値の型も明示する
    auto f = [&](auto f, ll n) -> mint {
        if (n <= 0) return 0;
        if (visited[n]) return memo[n];
        mint res = 1;
        res += f(f,n-2)*p;
        res += f(f,n-1)*q;
        visited[n] = true;
        return memo[n] = res;
    };

    // 出力
    cout << f(f,N) << endl;
}

void solve2() {
    ll N, P; cin >> N >> P;
    mint p = mint(P)/100;
    mint q = mint(1)-p;

    // dp[i] := HPがiのモンスターを倒すまでの攻撃回数の期待値
    vector<mint> dp(N+1, mint(0));
    dp[1] = mint(1); // pでもqでも倒せる
    for(ll i=2; i<=N; i++) {
        dp[i] = mint(1);  // 1回攻撃したあとは、
        dp[i] += dp[i-1]*q;  // 確率qでdp[i-1]に遷移
        dp[i] += dp[i-2]*p;  // 確率pでdp[i-2]に遷移
    }

    // 出力
    cout << dp[N] << endl;
}


// 攻撃回数の期待値 = 攻撃回数 * 確率
void solve3() {
    ll N, P; cin >> N >> P;
    mint p = mint(P)/100;
    mint q = mint(1)-p;

    // dp[n] := HPがnになるときの攻撃回数の期待値
    vector<mint> dp(N+1, 0);
    dp[N] = 0;
    dp[N-1] = 1;
    for(ll n=N-2; n>=0; n--) {
        dp[n] += (dp[n+1] + 1)*q;
        dp[n] += (dp[n+2] + 1)*p;
    }
    cout << dp[0] << endl;
}

int main() {
    // solve2();
    solve3();
    return 0;
}