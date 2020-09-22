#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    /* WA */
    int R, C, K;
    cin >> R >> C >> K;
    vector<vector<int>> grid(R, vector<int>(C, 0));
    for (int i=0; i<K; i++) {
        int r, c, v;
        cin >> r >> c >> v;
        grid.at(--r).at(--c) = v;
    }

    // dp[i][j][x] := i行j列目で、このマスの行でx個のアイテムを取ったときの価値の最大値
    // dpはlong longじゃないとダメ
    vector<vector<vector<ll>>> dp(R, vector<vector<ll>>(C, vector<ll>(4, 0)));
    dp[0][0][1] = grid[0][0];

    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            // grid[i-1][j]からgrid[i][j]へ移動する場合
            for (int x=0; x<4; x++) {
                if (i-1>=0) {
                // 拾わない場合
                    dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][x]);
                // 拾う場合
                    dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][x] + grid[i][j]);
                }
            }
            // grid[i][j-1]からgrid[i][j]へ移動する場合
            for (int x=0; x<4; x++) {
                if (j-1>=0) {
                    // 拾わない場合
                    dp[i][j][x] = max(dp[i][j][x], dp[i][j-1][x]);
                    // 拾う場合
                    if (x-1>=0) {
                        dp[i][j][x] = max(dp[i][j][x], dp[i][j-1][x-1] + grid[i][j]);
                    }
                }
            }
        }
    }

    // 答え
    ll ans = 0;
    for (int x=0; x<4; x++) {
        ans = max(ans, dp[R-1][C-1][x]);
    }
    cout << ans << endl;
}


void solve2() {
    /* 解説AC */
    int R, C, N;
    cin >> R >> C >> N;

    int d[3005][3005];
    rep(i, N) {
        int r, c, v;
        cin >> r >> c >> v;
        d[r-1][c-1] = v;
    }
    /* dpは long long じゃないとだめ*/
    ll dp[3005][3005];

}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}