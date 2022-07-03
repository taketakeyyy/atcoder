#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
// #define MOD 1000000007
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


ll MOD;
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

ll f(ll x) {
    // xのとき何桁？
    ll res = 0;
    while(x) {
        res++;
        x /= 10;
    }
    return res+1;
}


void solve_TLE() {
    // 愚直解のTLE解
    ll N; cin >> N;
    ll P; cin >> P;
    MOD = P;
    vector dp(N+1, vector<mint>(N));  // dp[i][j] := Sのi文字目までを決めて、|T|=jとなるときの場合の数
    for(ll w=1; w<=N; w++) {
        dp[w][f(w)] = 26;
    }

    for(ll i=1; i<=N; i++) {
        for(ll j=0; j<=N-1; j++) {
            for(ll w=1; w<=i; w++) {  // 次のSのブロックの文字数("aaa"なら3)
                if (j-f(w) < 0) continue;
                dp[i][j] += dp[i-w][j-f(w)] * 25;
            }
        }
    }

    mint ans;
    for(ll j=0; j<N; j++) {
        ans += dp[N][j];
    }
    cout << ans.x << endl;
}


void solve() {
    ll N; cin >> N;
    ll P; cin >> P;
    MOD = P;
    vector dp(N+1, vector<mint>(N));  // dp[i][j] := Sのi文字目までを決めて、|T|=jとなるときの場合の数
    vector ds(N+1, vector<mint>(N));  // 累積和用
    for(ll w=1; w<=N; w++) {  // w := 最初のブロックの文字数
        dp[w][f(w)] = 26;
    }

    const int ten[] = {0, 1, 10, 100, 1000, 10000};

    for(ll i=1; i<=N; i++) {
        for(ll j=0; j<=N-1; j++) {
            // 累積和使って高速化
            for(ll k=1; k<=4; k++) {
                ll nj = j-k-1;
                if (nj < 0) continue;
                ll lb = ten[k];  // 下界
                ll ub = ten[k+1];  // 上界
                ub = min(ub, i);
                if (lb >= ub) continue;
                // for(ll w=lb; w<ub; w++) {
                //     dp[i][j] += dp[i-w][nj]*25;
                // }
                dp[i][j] += (ds[i-lb][nj] - ds[i-ub][nj]) * 25;
            }
            ds[i][j] = ds[i-1][j] + dp[i][j];
        }
    }

    mint ans;
    for(ll j=0; j<N; j++) {
        ans += dp[N][j];
    }
    cout << ans.x << endl;
}


int main() {
    solve();
    return 0;
}