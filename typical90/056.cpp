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
    ll N, S; cin >> N >> S;
    vector<ll> A(N), B(N);

    // dp[i][s] := i日目にs円を作れるかどうか
    vector<vector<ll>> dp(N+1, vector<ll>(S+1, false));
    dp[0][0] = true;  // 0日目に0円は作れる
    for (ll i=1; i<N+1; i++) {
        ll a, b; cin >> a >> b;
        A[i-1] = a; B[i-1] = b;

        for (ll s=0; s<=S; s++) {
            if (0 <= s+a && s+a <= S && dp[i-1][s]) {
                dp[i][s+a] = true;
            }
            if (0 <= s+b && s+b <= S && dp[i-1][s]) {
                dp[i][s+b] = true;
            }
        }
    }

    // 答えを出力
    if (dp[N][S]) {
        // DP復元で答えを見つける
        string ans = "";
        ll s = S;
        for (ll i=N-1; i>=0; i--) {
            if (s-A[i]>=0 && dp[i][s-A[i]]) {
                ans = "A" + ans;
                s = s-A[i];
            }
            else {
                ans = "B" + ans;
                s = s-B[i];
            }
        }
        cout << ans << endl;
    }
    else {
        cout << "Impossible" << endl;
    }
}


int main() {
    solve();
    return 0;
}