#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    int N; cin >> N;
    vector<double> p(N+1, 0.0);
    for (int i=1; i<N+1; i++) {
        cin >> p[i];
    }

    // dp[i][j] := i枚目まで投げたときの表がj枚になる確率
    vector<vector<double>> dp(N+1, vector<double>(N+1, 1.0));
    dp[1][0] = 1.0-p[1];  // 1枚投げて表が0枚の確率
    dp[1][1] = p[1];    // 1枚投げて表が1枚の確率

    // dpを埋める
    for (int i=2; i<N+1; i++) {
        for (int j=0; j<i+1; j++) {
            if (j==0) {
                dp[i][j] = dp[i-1][0] * (1.0-p[i]);
            }
            else if (j==i) {
                dp[i][j] = dp[i-1][j-1]*p[i];
            }
            else {
                dp[i][j] = dp[i-1][j-1]*p[i] + dp[i-1][j]*(1.0-p[i]);
            }
        }
    }

    // 求める答えはdp[N][(N/2)+1]~dp[N][N]の総和
    double ans = 0.0;
    for (int j=(N/2)+1; j<N+1; j++) {
        ans += dp[N][j];
    }

    printf("%.10f", ans);
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}