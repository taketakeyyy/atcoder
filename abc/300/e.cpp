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


// 解説AC
// dp[n] := 持っている数がnである状態からスタートしたとき、最終的にNになる確率
void solve() {
    ll N; cin >> N;

    // メモ化再帰
    map<ll,mint> memo;
    auto dp = [&](auto self, ll n) -> mint {
        if (n > N) return 0;
        if (n == N) return 1;
        if (memo.count(n)) return memo[n];

        // 漸化式通りに実装
        mint total = 0;
        for(ll i=2; i<=6; i++) {
            total += self(self, i*n);
        }
        return memo[n] = total * mod_pow<ll>(5, MOD-2, MOD); // 1/5をかけている（フェルマーの小定理）
    };

    // 答え
    cout << dp(dp, 1) << endl;
}


// Nからスタートするパターン
// 割り切れる数字にしか遷移できないので少しシンプル
// dp[n] := 持っている数がnである状態からスタートして、最終的に1になる確率
void solve2() {
    ll N; cin >> N;

    map<ll, mint> memo;
    auto dp = [&](auto self, ll n) -> mint {
        if (n == 1) return 1;
        if (memo.count(n)) return memo[n];

        mint total = 0;
        for(ll i=2; i<=6; i++) {
            if (n%i == 0) total += self(self, n/i);
        }
        return memo[n] = total / 5;
    };

    cout << dp(dp, N) << endl;
}

int main() {
    solve();
    // solve2();
    return 0;
}