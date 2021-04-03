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

void f6(vector<ll>&dp, int i) {
    ll n = 6;
    while(1) {
        if (i-n < 0) break;
        dp[i] = min(dp[i], dp[i-n]+1);  // 6^q円
        n *= 6;
    }
}

void f9(vector<ll>&dp, int i) {
    ll n = 9;
    while(1) {
        if (i-n < 0) break;
        dp[i] = min(dp[i], dp[i-n]+1);  // 9^q円
        n *= 9;
    }
}

void solve() {
    ll N; cin >> N;
    // dp[N] := N円ちょうどを払うのに必要な最小の回数
    vector<ll> dp(N+1, INF);
    dp[0] = 0;
    for(int i=1; i<=N; i++) {
        dp[i] = min(dp[i], dp[i-1]+1);  // 1円
        f6(dp, i);  // 6^q円
        f9(dp, i);  // 6^q円
    }
    cout << dp[N] << endl;
}


int main() {
    solve();
    return 0;
}