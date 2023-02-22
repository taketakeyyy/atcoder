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


void solve() {
    ll N; cin >> N;
    string S; cin >> S;

    // A~J を 0~9 に直す
    vector<ll> A(N);
    for(ll i=0; i<N; i++) A[i] = S[i]-'A';

    // dp[i][j][k] := i文字目まで見て、選んだ文字の集合がjで、選んだ最新の文字がkのときの場合の数
    // k := 0 ~ 10 で、0~9はA~Jで、10は空文字
    vector dp(N, vector<vector<mint>>(1<<10, vector<mint>(11, 0)));
    // 初期値：0文字目だけやる
    dp[0][1<<A[0]][A[0]] = 1;
    dp[0][0][10] = 1;
    for(ll i=1; i<N; i++) {  // 高々1000
        // 今まで選んだ文字が空文字のときの遷移
        dp[i][0][10] += dp[i-1][0][10];  // 空文字への遷移
        dp[i][1<<A[i]][A[i]] += dp[i-1][0][10];  // A[i]を使うときの遷移

        // 今まで選んだ文字が空文字じゃないときの遷移
        for(ll j=0; j<(1<<10); j++) { // 1024
            for(ll k=0; k<10; k++) { // 10
                // i文字目を選ばないときの遷移
                dp[i][j][k] += dp[i-1][j][k];

                // i文字目を選ぶときの遷移
                if (A[i] == k) {
                    // ひとかたまりになるならOK
                    dp[i][j][k] += dp[i-1][j][k];
                }
                else {
                    if (j>>A[i]&1) continue; // すでに使われていて、ひとかたまりにできない
                    dp[i][j|(1<<A[i])][A[i]] += dp[i-1][j][k];
                }
            }
        }
    }

    mint ans = 0;
    for(ll j=0; j<(1<<10); j++) {
        for(ll k=0; k<10; k++) {
            ans += dp[N-1][j][k];
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}