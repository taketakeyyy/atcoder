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

ll H, W;
vector<string> grid;
vector<ll> dh = {-1, 1, 0, 0};
vector<ll> dw = {0, 0, -1, 1};
ll ans = 0;

void dfs(ll h, ll w, vector<vector<bool>>&visited, ll sh, ll sw, ll cost) {
    if (visited[h][w] && h==sh && w==sw) {
        // 一周した
        ans = max(ans, cost);
        return;
    }

    if (grid[h][w] == '#') return;
    if (visited[h][w]) return;

    visited[h][w] = true;

    for(ll i=0; i<4; i++) {
        ll nh = h + dh[i];
        ll nw = w + dw[i];
        if (nh<0 || H<=nh || nw<0 || W<=nw || grid[nh][nw]=='#') continue;

        dfs(nh, nw, visited, sh, sw, cost+1);
    }

    visited[h][w] = false;
}

void solve() {
    cin >> H >> W;
    grid.assign(H, "");
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }

    // すべてのマスを始点としてDFS全探索
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            vector<vector<bool>> visited(H, vector<bool>(W, false));
            dfs(h, w, visited, h, w, 0);
        }
    }

    // 答えを出力
    if (ans >= 4) {
        cout << ans << endl;
    }
    else {
        cout << -1 << endl;
    }
}


int main() {
    solve();
    return 0;
}