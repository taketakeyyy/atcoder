#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
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


void solve() {
    ll N; cin >> N;
    vector<ll> X(N+1), Y(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> X[i] >> Y[i];
    }

    // dp[i][j] := 左からi番目までの料理を食べて、状態がj(0:非毒, 1:毒)のときの美味しさの総和の最大値
    vector dp(N+1, vector<ll>(2, 0));
    dp[0][0] = 0; dp[0][1] = 0;
    for(ll i=1; i<=N; i++) {
        // 下げてもらうとき
        dp[i][0] = dp[i-1][0];
        dp[i][1] = dp[i-1][1];

        // 食べるとき
        if (X[i] == 0) {
            dp[i][0] = max(dp[i][0], dp[i-1][0]+Y[i]);
            dp[i][0] = max(dp[i][0], dp[i-1][1]+Y[i]);
        }
        else {
            dp[i][1] = max(dp[i][1], dp[i-1][0]+Y[i]);
        }
    }

    // 出力
    ll ans = max(dp[N][0], dp[N][1]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}