#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N; string S; cin >> S;
    // dp[i][j] := 左からi番目の時点で、「atcoder」のj文字目まで完成できる場合の数
    vector<vector<ll>> dp(N+1, vector<ll>(7, 0));

    for(int i=0; i<N; i++) {
        for(int j=0; j<7; j++) dp[i+1][j] = dp[i][j];

        switch (S[i]) {
            case 'a':
                dp[i+1][0] += 1;
                dp[i+1][0] %= MOD;
                break;
            case 't':
                dp[i+1][1] += dp[i][0];
                dp[i+1][1] %= MOD;
                break;
            case 'c':
                dp[i+1][2] += dp[i][1];
                dp[i+1][2] %= MOD;
                break;
            case 'o':
                dp[i+1][3] += dp[i][2];
                dp[i+1][3] %= MOD;
                break;
            case 'd':
                dp[i+1][4] += dp[i][3];
                dp[i+1][4] %= MOD;
                break;
            case 'e':
                dp[i+1][5] += dp[i][4];
                dp[i+1][5] %= MOD;
                break;
            case 'r':
                dp[i+1][6] += dp[i][5];
                dp[i+1][6] %= MOD;
                break;
            default:
                break;
        }
    }

    cout << dp[N][6] << endl;
}


int main() {
    solve();
    return 0;
}