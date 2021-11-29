#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    ll K; cin >> K;
    if (K%9 != 0) {
        cout << 0 << endl;
        return;
    }

    // dp[i] := 桁和がiの場合の通り数
    vector<ll> dp(K+1);
    dp[0] = 1;
    for(ll i=1; i<K+1; i++) {
        for(ll j=1; j<=9; j++) {
            if (i-j < 0) break;
            dp[i] += dp[i-j];
            dp[i] %= MOD;
        }
    }

    cout << dp[K] << endl;
}


int main() {
    solve();
    return 0;
}