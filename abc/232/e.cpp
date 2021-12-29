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

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

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
    ll H, W, K; cin >> H >> W >> K;
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;

    // dp[k][i][j] := k回動かしたときに、x2行にいて（i）、y2列にいて(j)、その場合の通り数
    vector dp(K+1, vector<vector<mint>>(2, vector<mint>(2, 0)));
    if (x1==x2) {
        if (y1==y2) {
            dp[0][1][1] = 1;
        }
        else {
            dp[0][1][0] = 1;
        }
    }
    else {
        if (y1==y2) {
            dp[0][0][1] = 1;
        }
        else {
            dp[0][0][0] = 1;
        }
    }

    // これが正解
    mint x2_masu = W-1;  // x2上のマスの数（ゴールは除く）
    mint y2_masu = H-1;  // y2上のマスの数（ゴールは除く）

    for(ll k=1; k<=K; k++) {
        dp[k][0][0] += dp[k-1][0][0]*(W-2+H-2);
        dp[k][0][0] += dp[k-1][1][0]*y2_masu;
        dp[k][0][0] += dp[k-1][0][1]*x2_masu;

        dp[k][1][0] += dp[k-1][0][0];
        dp[k][1][0] += dp[k-1][1][0]*(x2_masu-1);
        dp[k][1][0] += dp[k-1][1][1]*x2_masu;

        dp[k][0][1] += dp[k-1][0][0];
        dp[k][0][1] += dp[k-1][0][1]*(y2_masu-1);
        dp[k][0][1] += dp[k-1][1][1]*y2_masu;

        dp[k][1][1] += dp[k-1][1][0];
        dp[k][1][1] += dp[k-1][0][1];
    }

    cout << dp[K][1][1] << endl;
}

int main() {
    solve();
    return 0;
}