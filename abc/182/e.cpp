#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve2(){
    /* TLE */
    int H, W, N, M;
    cin >> H >> W >> N >> M;
    vector<vector<int>> grid(H, vector<int>(W, 0));  // 電球：1, ブロック:-1
    vector<vector<int>> ans_grid(H, vector<int>(W, 0));  // 照らせる箇所:1, 照らせない箇所:0
    vector<pair<int, int>> lights;
    for (int i=0; i<N; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        pair<int, int> p(a,b);
        lights.push_back(p);
    }
    for (int i=0; i<M; i++) {
        int c, d;
        cin >> c >> d;
        c--; d--;
        grid[c][d] = -1;
    }

    for (int i=0; i<lights.size(); i++) {
        int h, w;
        tie(h,w) = lights[i];
        grid[h][w] = 1; ans_grid[h][w] = 1;

        // 左側走査
        for (int nw=w-1; nw>=0; nw--) {
            if (grid[h][nw] == -1) break;
            ans_grid[h][nw] = 1;
        }
        // 右側走査
        for (int nw=w+1; nw<W; nw++) {
            if (grid[h][nw] == -1) break;
            ans_grid[h][nw] = 1;
        }
        // 上側走査
        for (int nh=h-1; nh>=0; nh--) {
            if (grid[nh][w] == -1) break;
            ans_grid[nh][w] = 1;
        }
        // 下側走査
        for (int nh=h+1; nh<H; nh++) {
            if (grid[nh][w] == -1) break;
            ans_grid[nh][w] = 1;
        }
    }

    // 確認
    // for (int h=0; h<H; h++) {
    //     for (int w=0; w<W; w++) {
    //         cout << grid[h][w] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "---" << endl;
    // for (int h=0; h<H; h++) {
    //     for (int w=0; w<W; w++) {
    //         cout << ans_grid[h][w] << " ";
    //     }
    //     cout << endl;
    // }

    // 答え
    int ans = 0;
    for (int h=0; h<H; h++) {
        ans += accumulate(ans_grid[h].begin(), ans_grid[h].end(), 0);
    }
    cout << ans << endl;
}


void solve(){
    int H, W, N, M;
    cin >> H >> W >> N >> M;
    vector<vector<int>> grid(H, vector<int>(W, 0));  // 電球：1, ブロック:-1
    vector<vector<int>> h_grid(H, vector<int>(W, 0));  // 縦方向の照らせる箇所:1, 照らせない箇所:0
    vector<vector<int>> w_grid(H, vector<int>(W, 0));  // 横方向の照らせる箇所:1, 照らせない箇所:0
    vector<pair<int, int>> lights;
    for (int i=0; i<N; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        pair<int, int> p(a,b);
        lights.push_back(p);
    }
    for (int i=0; i<M; i++) {
        int c, d;
        cin >> c >> d;
        c--; d--;
        grid[c][d] = -1;
    }

    for (int i=0; i<N; i++) {
        int h, w;
        tie(h,w) = lights[i];

        // h_gridを埋める
        if (h_grid[h][w] != 1) { // まだ照らされていないか？
            h_grid[h][w] = 1;
            for (int nh=h-1; nh>=0; nh--) {
                if (grid[nh][w] == -1) break;
                h_grid[nh][w] = 1;
            }
            for (int nh=h+1; nh<H; nh++) {
                if (grid[nh][w] == -1) break;
                h_grid[nh][w] = 1;
            }
        }

        // w_gridを埋める
        if (w_grid[h][w] != 1) { // まだ照らされていないか？
            w_grid[h][w] = 1;
            for (int nw=w-1; nw>=0; nw--) {
                if(grid[h][nw] == -1) break;
                w_grid[h][nw] = 1;
            }
            for (int nw=w+1; nw<W; nw++) {
                if(grid[h][nw] == -1) break;
                w_grid[h][nw] = 1;
            }
        }
    }

    // 確認
    // for (int h=0; h<H; h++) {
    //     for (int w=0; w<W; w++) {
    //         cout << h_grid[h][w] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "---" << endl;

    // for (int h=0; h<H; h++) {
    //     for (int w=0; w<W; w++) {
    //         cout << w_grid[h][w] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "---" << endl;

    // 出力
    int ans = 0;
    for (int h=0; h<H; h++) {
        for (int w=0; w<W; w++) {
            if (h_grid[h][w]==1 || w_grid[h][w]==1) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}