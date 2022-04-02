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
    ll N, K; cin >> N >> K;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];

    vector<bool> dp(2);  // dp[x] := 前回x(AまたはB)を選ぶことができたかどうか
    dp[0] = true;
    dp[1] = true;
    for(ll i=1; i<N; i++) {
        vector<bool> pdp(2, false);
        swap(pdp, dp);

        if (pdp[0]) {
            if (abs(A[i-1]-A[i]) <= K) {
                dp[0] = true;
            }
            if (abs(A[i-1]-B[i]) <= K) {
                dp[1] = true;
            }
        }
        if (pdp[1]) {
            if (abs(B[i-1]-A[i]) <= K) {
                dp[0] = true;
            }
            if (abs(B[i-1]-B[i]) <= K) {
                dp[1] = true;
            }
        }

        if (!dp[0] && !dp[1]) {
            cout << "No" << endl;
            return;
        }
    }

    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}