#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
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


// 期待値DPの解法
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=1; i<=N-1; i++) cin >> A[i];

    // dp[x] := 現在いるマスがxの状態で、終了するまでのサイコロを降る回数の期待値
    vector<mint> dp(N+1, 0);
    vector<mint> S(N+2, 0);  // S[x] := dp[N]からdp[x]までの累積和
    dp[N] = 0; S[N] = 0;
    for(ll x=N-1; x>=1; x--) {
        mint p = mint(1)/(A[x]+1); // 確率
        mint total = (S[x+1] - S[x+A[x]+1]);
        dp[x] = mint(1)/(mint(1)-p) + p/(mint(1)-p)*total;
        S[x] = S[x+1] + dp[x];
    }
    cout << dp[1] << endl;
}


// メモ化再帰の解法
void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=1; i<=N-1; i++) cin >> A[i];

    // メモ化再帰 f(x) := 現在いるマスがxの状態で、終了するまでのサイコロを降る回数の期待値
    vector<bool> visited(N+1, false); // visited[x] := memo[x]はメモ済か？
    vector<mint> memo(N+1, 0); // memo[x] := f(x)のメモ値
    vector<mint> S(N+2, 0);  // S[x] := f(N)からf(x)までの累積和
    auto f = [&](auto self, ll x) -> mint {
        if (x >= N) return 0;
        if (visited[x]) return memo[x];

        // f(x)を計算する
        mint p = mint(1)/(A[x]+1);  // 確率
        mint total = (S[x+1] - S[x+A[x]+1]);
        memo[x] = mint(1)/(mint(1)-p) + p/(mint(1)-p)*total;
        S[x] = S[x+1] + memo[x];
        return memo[x];
    };

    // 出力
    cout << f(f, 1) << endl;
}



int main() {
    solve();
    return 0;
}