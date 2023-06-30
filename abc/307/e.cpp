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

/**
 * @brief a^{n} mod m の計算を、繰り返し二乗法で求める
 * 計算量：O(log n)
 **/
template<typename T>
T mod_pow(T a, T n, T m) {
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

void solve() {
    ll N, M; cin >> N >> M;
    // dp[i][f] := i人目まで数を割り当てる方法のうち、i人目に割り当てた数が1人目に割り当てた数と同じかどうか（f=0:違う, f=1:同じ）なものの個数
    vector dp(N+1, vector<mint>(2, 0));
    dp[1][1] = M;
    for(ll i=1; i<N; i++) {
        dp[i+1][0] += dp[i][0]*(M-2); // 0-...-(M-1)-(M-2) := i+1人目は、1人目とi人目と違う数字なので、M-2通りの遷移がある
        dp[i+1][0] += dp[i][1]*(M-1); // 0-...-0-(M-1) := i+1人目は、M-1通りの遷移がある
        dp[i+1][1] += dp[i][0]; // 0-...-(M-1)-0 := i+1人目は、1人目と同じ数字なので、1通りの遷移
    }
    cout << dp[N][0] << endl;
}


// 円環の問題は、「特別な意味のものを先頭に固定」 + 「末尾に先頭のものを追加」
void solve2() {
    ll N, M; cin >> N >> M;
    // dp[i][f] := i人目まで数を割り当てる方法のうち、i人目に割り当てた数が1人目に割り当てた数と同じかどうか（f=0:違う, f=1:同じ）なものの個数
    // 求める答えはdp[N+1][1]
    vector dp(N+2, vector<mint>(2, 0));
    dp[1][1] = M;
    for(ll i=1; i<N+1; i++) {
        dp[i+1][0] += dp[i][0]*(M-2); // 0-...-(M-1)-(M-2) := i+1人目は、1人目とi人目と違う数字なので、M-2通りの遷移がある
        dp[i+1][0] += dp[i][1]*(M-1); // 0-...-0-(M-1) := i+1人目は、M-1通りの遷移がある
        dp[i+1][1] += dp[i][0]; // 0-...-(M-1)-0 := i+1人目は、1人目と同じ数字なので、1通りの遷移
    }
    cout << dp[N+1][1] << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}