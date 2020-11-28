#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    /* けんちょんAC（これが一番わかりやすい）
    https://drken1215.hatenablog.com/entry/2020/11/16/204900
    */
    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (int i=0; i<H; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> dp(H+1, vector<int>(W+1, 0));
    vector<vector<int>> X(H+1, vector<int>(W+1, 0));  // x方向の累積和
    vector<vector<int>> Y(H+1, vector<int>(W+1, 0));  // y方向の累積和
    vector<vector<int>> Z(H+1, vector<int>(W+1, 0));  // ななめ方向の累積和
    dp[1][1] = 1;
    for (int i=1; i<=H; i++) {
        for (int j=1; j<=W; j++) {
            // 壁だったらこれまでの累積和をリセット
            if (grid[i-1][j-1]=='#') {
                X[i][j] = Y[i][j] = Z[i][j] = 0;
                continue;
            }

            // 3方向からの累積和を合算
            dp[i][j]+=X[i][j-1];    dp[i][j]%=MOD;
            dp[i][j]+=Y[i-1][j];    dp[i][j]%=MOD;
            dp[i][j]+=Z[i-1][j-1];  dp[i][j]%=MOD;

            // 累積和を更新する
            X[i][j] = X[i][j-1] + dp[i][j];    X[i][j]%=MOD;
            Y[i][j] = Y[i-1][j] + dp[i][j];    Y[i][j]%=MOD;
            Z[i][j] = Z[i-1][j-1] + dp[i][j];  Z[i][j]%=MOD;
        }
    }
    cout << dp[H][W] << endl;
}


void solve3() {
    /* 解説AC （ちょっとよくわからん・・・）*/
    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (int i=0; i<H; i++) {
        cin >> grid[i];
    }

    // dp[i][j] := マス(i,j)にたどり着く方法
    // dp[i][j] := Σ(i,jに一手でたどり着ける(i',j')) (dp[i'][j'])
    // O(H*W*(H+W))くらいかかってしまう
    // 同じ区間を何回も足しているので、累積和を使ってやると良さそう

    // dpx[i][j] = 横方向に移動中の(i,j)の上空にいる
    // dpy[i][j] = dpx[i][j-1] + dp[i][j]
    // dpxy[i][j] =
    // dp[i][j] = dpx[i][j] + dpy[i][j] + dpxy[i][j]
    vector<vector<int>> dp(H, vector<int>(W, 0));
    vector<vector<int>> dpx(H, vector<int>(W, 0));
    vector<vector<int>> dpy(H, vector<int>(W, 0));
    vector<vector<int>> dpxy(H, vector<int>(W, 0));
    dp[0][0] = 1;
    dpx[0][0] = 1;
    dpy[0][0] = 1;
    dpxy[0][0] = 1;

    for (int i=0; i<H; i++) {
        for (int j=0; j<W; j++) {
            if (i==0 && j==0) continue;
            if (grid[i][j]=='#') continue;

            // 累積和を更新
            if (j-1>=0) { dpx[i][j] += dpx[i][j-1]; dpx[i][j]%=MOD;}
            if (i-1>=0) { dpy[i][j] += dpy[i-1][j]; dpy[i][j]%=MOD;}
            if (i-1>=0 && j-1>=0) { dpxy[i][j] += dpxy[i-1][j-1]; dpxy[i][j]%=MOD;}
            // 着陸（3方向からの累積和を合算）
            dp[i][j] += dpx[i][j]; dp[i][j]%=MOD;
            dp[i][j] += dpy[i][j]; dp[i][j]%=MOD;
            dp[i][j] += dpxy[i][j]; dp[i][j]%=MOD;
            // 離陸（累積和を更新）
            dpx[i][j] += dp[i][j]; dpx[i][j]%=MOD;
            dpy[i][j] += dp[i][j]; dpy[i][j]%=MOD;
            dpxy[i][j] += dp[i][j]; dpxy[i][j]%=MOD;
        }
    }
    cout << dp[H-1][W-1] << endl;

}

void solve2(){
    /* TLE */
    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (int i=0; i<H; i++) {
        cin >> grid[i];
    }

    // dp[h][w] := (h,w)座標まで見たときの移動する方法
    vector<vector<int>> dp(H, vector<int>(W, 0));
    dp[0][0] = 1;  // スタート地点
    for (int h=0; h<H; h++) {
        for (int w=0; w<W; w++) {
            if (grid[h][w]=='#') continue;
            // 右方向
            int nw = w+1;
            while (nw<W && grid[h][nw]!='#') {  // ここで時間がかかるO(W)
                dp[h][nw] += dp[h][w];
                dp[h][nw] %= MOD;
                nw++;
            }
            // 下方向
            int nh = h+1;
            while (nh<H && grid[nh][w]!='#') {  // ここで時間がかかるO(H)
                dp[nh][w] += dp[h][w];
                dp[nh][w] %= MOD;
                nh++;
            }
            // 右下方向
            nh = h+1; nw = w+1;
            while (nh<H && nw<W && grid[nh][nw]!='#') {  // ここで時間がかかるO(min(H,W))
                dp[nh][nw] += dp[h][w];
                dp[nh][nw] %= MOD;
                nh++; nw++;
            }
        }
    }

    // for (int h=0; h<H; h++) {
    //     for (int w=0; w<W; w++) {
    //         cout << dp[]
    //     }
    // }

    cout << dp[H-1][W-1] << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}