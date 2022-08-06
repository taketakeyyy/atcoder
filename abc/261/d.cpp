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
    ll N, M; cin >> N >> M;
    vector<ll> X(N+1);
    for(ll i=1; i<=N; i++) cin >> X[i];
    map<ll,ll> bonusmp;
    for(ll i=0; i<M; i++) {
        ll c, y; cin >> c >> y;
        bonusmp[c] = y;
    }

    // dp[i][j] := 現在i回目のコイントスで、カウンタ値がjのときのお金の最大値
    vector dp(N+1, vector<ll>(N+1, -1));
    dp[0][0] = 0;
    for(ll i=1; i<=N; i++) {
        for(ll j=0; j<=N; j++) {
            // 表が出たとき
            if ((i-1>=0) && (j-1>=0) && (dp[i-1][j-1]!=-1)) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + X[i] + bonusmp[j]);
            }
            // 裏が出たとき
            if (i-1>=0) {
                dp[i][0] = max(dp[i][0], dp[i-1][j]);
            }
        }
    }

    // 出力
    ll ans = 0;
    for(ll j=0; j<=N; j++) {
        ans = max(ans, dp[N][j]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}