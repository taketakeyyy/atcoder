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
    ll S; cin >> S;
    if (S < 3) {
        cout << 0 << endl;
        return;
    }

    // dp[i] := 位置iで区切ったときの場合の数
    // S=7:  o o o o o o o
    //      ^ ^ ^ ^ ^ ^ ^ ^
    vector<ll> dp(S+1, 0);
    ll total = 0;  // 累積和
    dp[0] = 1;
    for(int i=1; i<S+1; i++) {
        // for(int j=0; j<=i-3; j++) {
        //     dp[i] += dp[j];
        //     dp[i] %= MOD;
        // }
        if (i-3 < 0) continue;
        total += dp[i-3];
        total %= MOD;
        dp[i] = total;
    }
    cout << dp[S] << endl;
}


int main() {
    solve();
    return 0;
}