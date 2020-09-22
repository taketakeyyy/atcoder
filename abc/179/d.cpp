#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 998244353
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


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


void solve(){
    int N, K;
    cin >> N >> K;
    vector<int> l(K), r(K);
    rep(i, K) cin >> l[i] >> r[i];

    // dp[i] := 左からiマス目にいるときの、行き方の数
    vector<mint> dp(N+1, 0);     // dp
    vector<mint> dpsum(N+1, 0);  // 累積和
    dp[1] = 1;
    dpsum[1] = 1;
    for (int i=2; i<=N; i++) {
        rep(j, K) {
            // [l[j], r[j]]
            int li = i-r[j];
            int ri = i-l[j];
            if (ri < 0) continue;
            li = max(li, 1);  // 負になると困るので
            dp[i] += dpsum[ri]-dpsum[li-1]; // dp[li]~dp[ri]
        }
        dpsum[i] = dpsum[i-1]+dp[i];
    }
    cout << dp[N] << endl;
}


void solve2() {
  int N, K;
  cin >> N >> K;
  vector<int> l(K), r(K);
  rep(i, K) cin >> l[i] >> r[i];

  // dp[i] := 左からiマス目にいるときの、行き方の総数（貰うDP）
  vector<mint> dp(N+1, 0);
  vector<mint> dpsum(N+1, 0);  // 累積和
  dp[1] = 1; dpsum[1] = 1;
  for (int i=2; i<N+1; i++) {
    for (int j=0; j<K; j++) {
      int li = i - r[j];
      int ri = i - l[j];
      if (ri < 1) continue;
      li = max(li, 1);
      dp[i] += dpsum[ri] - dpsum[li-1];
    }
    dpsum[i] = dpsum[i-1] + dp[i];
  }
  cout << dp[N] << endl;
}


int main(int argc, char const *argv[]){
    solve2();
    return 0;
}