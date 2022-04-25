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
    // ただし、i >= i' かつ j >= j'
    // すなわち、かならず座標(i,j)は(i',j')より右下にくる
    // dp[i'][j'] := 左上を起点として、座標(i',j')まで見たときの建設費用の最小値。ただし座標(i',j')は含まない。
    vector<vector<ll>> dp(H, vector<ll>(W, INF));
    ll ans = INF;
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            if (i-1 >= 0) dp[i][j] = min(dp[i][j], dp[i-1][j]);
            if (j-1 >= 0) dp[i][j] = min(dp[i][j], dp[i][j-1]);
            ans = min(ans, dp[i][j] + A[i][j]+C*(i+j));

            // dp(i,j)を更新
            dp[i][j] = min(dp[i][j], A[i][j] - C*(i+j));
        }
    }

    // もう1パターン考慮する必要がある。
    // ただし、i <= i' かつ j >= j'
    // すなわち、かならず座標(i,j)は(i',j')より左下にくる
    // 求める答え：A[i][j]+C(i-j) + A[i'][j']+C(j'-i') の最小値
    // dp[i'][j'] := 右上を起点として、座標(i',j')まで見たときの建設費用の最小値。ただし座標(i',j')は含まない。
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) dp[h][w] = INF;
    }

    for(ll i=0; i<H; i++) {
        for(ll j=W-1; j>=0; j--) {
            if (i-1 >= 0)   dp[i][j] = min(dp[i][j], dp[i-1][j]);
            if (j+1 <= W-1) dp[i][j] = min(dp[i][j], dp[i][j+1]);
            ans = min(ans, dp[i][j] + A[i][j]+C*(i-j));

            // dpの更新
            dp[i][j] = min(dp[i][j], A[i][j]+C*(j-i));
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}