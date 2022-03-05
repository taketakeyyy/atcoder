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

ll N;
ll ans = 0;

void solve() {
    cin >> N;
    vector<vector<ll>> dp(N, vector<ll>(10, 0));  // dp[i][k] := 左からi桁目がkのときの場合の数
    for(ll k=1; k<=9; k++) dp[0][k] = 1;
    for(ll i=1; i<N; i++) {
        for(ll k=1; k<=9; k++) {
            dp[i][k] += dp[i-1][k];
            dp[i][k] %= MOD;
            if (k-1 >= 1) {
                dp[i][k] += dp[i-1][k-1];
                dp[i][k] %= MOD;
            }
            if (k+1 <= 9) {
                dp[i][k] += dp[i-1][k+1];
                dp[i][k] %= MOD;
            }
        }
    }

    ll ans = 0;
    for(ll k=1; k<=9; k++) {
        ans += dp[N-1][k];
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}