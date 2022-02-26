#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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
    vector<ll> A(N+1), B(N+1);
    for(ll i=1; i<=N; i++) cin >> A[i];
    for(ll i=1; i<=N; i++) cin >> B[i];

    vector<vector<ll>> dp(N+1, vector<ll>(3001, 0));  // dp[i][j] := iまで見て、c[i]がjになれる場合の数
    vector<ll> ruiseki(3001, 0);
    for(ll j=0; j<=3000; j++) {
        if (A[1] <= j && j <= B[1]) dp[1][j] = 1;
        if (j-1 >= 0) {
            ruiseki[j] = ruiseki[j-1] + dp[1][j];
            ruiseki[j] %= MOD;
        }
        else {
            ruiseki[j] = dp[1][j];
        }
    }
    for(ll i=2; i<=N; i++) {
        for(ll c=A[i]; c<=B[i]; c++) {
            // for(ll k=0; k<=c; k++) {  // ここの0~cの和、累積和を保持することで計算をO(1)にできないか？
            //     dp[i][c] += dp[i-1][k];
            //     dp[i][c] %= MOD;
            // }
            dp[i][c] += ruiseki[c];
            dp[i][c] %= MOD;
        }

        // 累積和更新
        for(ll j=0; j<=3000; j++) {
            if (j-1 >= 0) {
                ruiseki[j] = ruiseki[j-1] + dp[i][j];
                ruiseki[j] %= MOD;
            }
            else {
                ruiseki[j] = dp[i][j];
            }
        }
    }

    ll ans = 0;
    for(ll i=0; i<=3000; i++) {
        ans += dp[N][i];
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}