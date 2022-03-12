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
    string s;
    cin >> s;

    // dp[i][k] := i番目までに、"chokudai"のk文字目まで完成できる場合の数
    vector<vector<ll>> dp(s.size(), vector<ll>(9, 0));
    for(ll i=0; i<s.size(); i++) {
        if (i-1 >= 0) {
            dp[i][1] = dp[i-1][1];
            dp[i][2] = dp[i-1][2];
            dp[i][3] = dp[i-1][3];
            dp[i][4] = dp[i-1][4];
            dp[i][5] = dp[i-1][5];
            dp[i][6] = dp[i-1][6];
            dp[i][7] = dp[i-1][7];
            dp[i][8] = dp[i-1][8];
        }

        if (s[i] == 'c') {
            if (i-1 >= 0) {
                dp[i][1] += 1;
                dp[i][1] %= MOD;
            }
            else {
                dp[i][1] = 1;
            }
        }
        else if (s[i] == 'h') {
            if (i-1 >= 0) {
                dp[i][2] += dp[i-1][1];
                dp[i][2] %= MOD;
            }
        }
        else if (s[i] == 'o') {
            if (i-1 >= 0) {
                dp[i][3] += dp[i-1][2];
                dp[i][3] %= MOD;
            }
        }
        else if (s[i] == 'k') {
            if (i-1 >= 0) {
                dp[i][4] += dp[i-1][3];
                dp[i][4] %= MOD;
            }
        }
        else if (s[i] == 'u') {
            if (i-1 >= 0) {
                dp[i][5] += dp[i-1][4];
                dp[i][5] %= MOD;
            }
        }
        else if (s[i] == 'd') {
            if (i-1 >= 0) {
                dp[i][6] += dp[i-1][5];
                dp[i][6] %= MOD;
            }
        }
        else if (s[i] == 'a') {
            if (i-1 >= 0) {
                dp[i][7] += dp[i-1][6];
                dp[i][7] %= MOD;
            }
        }
        else if (s[i] == 'i') {
            if (i-1 >= 0) {
                dp[i][8] += dp[i-1][7];
                dp[i][8] %= MOD;
            }
        }
    }

    cout << dp[s.size()-1][8] << endl;
}


int main() {
    solve();
    return 0;
}