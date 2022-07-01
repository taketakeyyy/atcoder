#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
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


void solve() {
    ll N, L; cin >> N >> L;
    vector<ll> dp(N+1, 0);
    dp[0] = 1;
    for(ll i=1; i<=N; i++) {
        if (i-L >= 0) {
            dp[i] += (dp[i-1] + dp[i-L]) % MOD;
        }
        else {
            dp[i] += dp[i-1];
        }
        dp[i] %= MOD;
    }

    // 出力
    cout << dp[N] << endl;
}


int main() {
    solve();
    return 0;
}