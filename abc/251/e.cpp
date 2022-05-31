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
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][j] := 左からi番目までを選んで、A[i]の餌を与えたかどうか（j=0 or 1）のときの、費用の最小値
    // 0番目を必ず選ぶDP
    vector<vector<ll>> dp1(N, vector<ll>(2, INF));
    dp1[0][1] = A[0];
    dp1[1][0] = A[0];
    for(ll i=1; i<N; i++) {
        // 餌を与えないとき
        dp1[i][0] = min(dp1[i][0], dp1[i-1][1]);
        // 餌を与えるとき
        dp1[i][1] = min(dp1[i][1], dp1[i-1][0]+A[i]);
        dp1[i][1] = min(dp1[i][1], dp1[i-1][1]+A[i]);
    }

    // N-1番目を必ず選ぶDP
    vector<vector<ll>> dp2(N, vector<ll>(2, INF));
    dp2[N-1][1] = A[N-1];
    dp2[N-2][0] = A[N-1];
    for(ll i=N-2; i>=0; i--) {
        // 餌を与えないとき
        dp2[i][0] = min(dp2[i][0], dp2[i+1][1]);
        // 餌を与えるとき
        dp2[i][1] = min(dp2[i][1], dp2[i+1][0]+A[i]);
        dp2[i][1] = min(dp2[i][1], dp2[i+1][1]+A[i]);
    }

    ll ans1 = min(dp1[N-1][0], dp1[N-1][1]);
    ll ans2 = min(dp2[0][0], dp2[0][1]);
    cout << min(ans1, ans2) << endl;
}


int main() {
    solve();
    return 0;
}