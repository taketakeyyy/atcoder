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
    ll H, W, C; cin >> H >> W >> C;
    vector<vector<ll>> A(H, vector<ll>(W, 0));
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            cin >> A[i][j];
        }
    }

    // 求める答え：A[i][j]+A[i'][j']+C(i-i' + j-j') の最小値
    // S[i][j] = A[i][j] + C(i+j)
    // T[i][j] = A[i][j] - C(i+j)
    // 求める答え：S[i][j] + T[i'][j'] の最小値
    // ただし、i > i' かつ j > j'
    // dp[i][j] := 左上を起点として、座標(i,j)まで見たときの建設費用の最小値
    vector<vector<ll>> dp(H, vector<ll>(W, INF));
    ll ans = INF;
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            // if (i==0 && j==0) continue;
            if (i-1 >= 0) dp[i][j] = min(dp[i][j], dp[i-1][j]);
            if (j-1 >= 0) dp[i][j] = min(dp[i][j], dp[i][j-1]);
            ans = min(ans, A[i][j] + C*(i+j) + dp[i][j]);

            ll now = A[i][j] - C*(i+j);  // 今のマス
            dp[i][j] = min(dp[i][j], now);
        }
    }
}


int main() {
    solve();
    return 0;
}