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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

ll H, W, A, B;
vector<vector<ll>> grid;
ll ans = 0;

void dfs(ll h, ll w, ll a, ll b) {
    // 終了条件
    if (h==H && w==0) {
        if (a==A && b==B) {
            ans++;
            return;
        }
        else {
            return;
        }
    }

    if (grid[h][w]==0) {
        // まだタイルが埋められていないなら、3パターンのうちどれかのタイルの敷き詰め方を選ぶ
        if (h+1<H && grid[h+1][w]==0 && a<A) {
            // 2x1の敷き詰め方
            grid[h][w] = 1;
            grid[h+1][w] = 1;
            if (w+1<W) {
                dfs(h, w+1, a+1, b);
            }
            else {
                dfs(h+1, 0, a+1, b);
            }
            grid[h][w] = 0;
            grid[h+1][w] = 0;
        }

        if (w+1<W && grid[h][w+1]==0 && a<A) {
            // 1x2の敷き詰め方
            grid[h][w] = 1;
            grid[h][w+1] = 1;
            if (w+2<W) {
                dfs(h, w+2, a+1, b);
            }
            else {
                dfs(h+1, 0, a+1, b);
            }
            grid[h][w] = 0;
            grid[h][w+1] = 0;
        }

        if (b<B) {
            // 1x1の敷き詰め方
            grid[h][w] = 1;
            if (w+1<W) {
                dfs(h, w+1, a, b+1);
            }
            else {
                dfs(h+1, 0, a, b+1);
            }
            grid[h][w] = 0;
        }

    }
    else {
        if (w+1<W) {
            dfs(h, w+1, a, b);
        }
        else {
            dfs(h+1, 0, a, b);
        }
    }
}

void solve() {
    cin >> H >> W >> A >> B;
    grid.resize(H);
    for(int i=0; i<H; i++) {
        grid[i].resize(W,0);
    }
    // HWが小さいので、全探索を考える
    // 左上から、1x2、2x1、1x1の3パターンのタイルのどれかで埋めることを考える。
    // - どこかで矛盾が生じるなどしたら枝切り
    // - 最後まで作れたら、OK
    dfs(0,0,0,0);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}