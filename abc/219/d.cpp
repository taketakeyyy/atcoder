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
    ll N; cin >> N;
    ll X, Y; cin >> X >> Y;

    // dp[i][a][b] := i番目までの弁当を選んで、たこ焼きa個、たい焼きb個を食べれるときの、弁当の最小値
    vector<vector<vector<ll>>> dp(301, vector<vector<ll>>(301, vector<ll>(301, INF)));
    dp[0][0][0] = 0;
    for(ll i=1; i<=N; i++) {
        dp[i][0][0] = 0;
        ll A, B; cin >> A >> B;

        // この弁当を食べない場合
        for(ll a=0; a<=300; a++) {
            for(ll b=0; b<=300; b++) {
                if (dp[i-1][a][b] != INF) {
                    dp[i][a][b] = min(dp[i][a][b], dp[i-1][a][b]);
                }
            }
        }
        // この弁当を食べた場合
        for(ll a=0; a<=300; a++) {
            for(ll b=0; b<=300; b++) {
                if (dp[i-1][a][b] != INF) {
                    dp[i][min<ll>(a+A, 300)][min<ll>(b+B, 300)] = min(dp[i][min<ll>(a+A, 300)][min<ll>(b+B, 300)], dp[i-1][a][b]+1);
                }
            }
        }
    }

    ll ans = INF;
    for(ll a=X; a<=300; a++) {
        for(ll b=Y; b<=300; b++) {
            ans = min(ans, dp[N][a][b]);
        }
    }
    if (ans == INF) ans = -1;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}