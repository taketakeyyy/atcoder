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
void chmax(double& x, double y) { x = max(x,y); }
void chmin(double& x, double y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> P(N);
    for(ll i=0; i<N; i++) cin >> P[i];

    // 分母部分を計算
    vector<double> bunbo(N+1);
    for(ll k=1; k<=N; k++) {
        for(ll i=1; i<=k; i++) {
            bunbo[k] += pow(0.9,k-i);
        }
    }

    // 分子部分を計算
    // dp[i][k] := i回目のコンテストまで見て、k個選ぶ場合の、分子の最大値
    vector<double> dp(N+1, -INF);
    dp[0] = 0.0;
    for(ll i=0; i<N; i++) {
        // i回目のコンテストを選ばない場合
        auto olddp = dp;

        // i回目のコンテストを選ぶ場合
        for(ll k=0; k<N; k++) {
            if (olddp[k] == -INF) continue;
            chmax(dp[k+1], olddp[k]*0.9+P[i]);
        }
    }

    // 答え
    double ans = -INF;
    for(ll k=1; k<=N; k++) {
        chmax(ans, dp[k]/bunbo[k] - (1200.0/sqrt(k)));
    }
    printf("%.10f\n", ans);
}


int main() {
    solve();
    return 0;
}