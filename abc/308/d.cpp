#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

ll H, W;

map<char,char> mp = {{'s','n'}, {'n','u'}, {'u','k'}, {'k','e'}, {'e','s'}};

bool is_inside(ll h, ll w) {
    return (h>=0 && h<H && w>=0 && w<W);
}

bool dfs(ll h, ll w, vector<string> &grid, vector<vector<bool>> &visited, vector<vector<bool>> &memo) {
    if (memo[h][w]) return false;
    memo[h][w] = true;

    if (h==H-1 && w==W-1) {
        return true;
    }

    for(ll vi=0; vi<4; vi++) {
        ll nh = h + vy[vi];
        ll nw = w + vx[vi];
        if (!is_inside(nh, nw)) continue;
        if (visited[nh][nw]) continue;
        if (mp[grid[h][w]] != grid[nh][nw]) continue;
        visited[nh][nw] = true;
        if (dfs(nh, nw, grid, visited, memo)) return true;
        visited[nh][nw] = false;
    }
    return false;
}

// DFS解
void solve() {
    cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) cin >> grid[i];
    vector visited(H, vector<bool>(W, false));
    vector memo(H, vector<bool>(W, false)); // メモ化探索済み？
    visited[0][0] = true;
    if (dfs(0, 0, grid, visited, memo)) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}

// 拡張BFS解（どこの方向から来たのかの情報を持たせる）
void solve2() {
    cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) cin >> grid[i];
    // visited[h][w][dir] := (h,w)にdirの方向から来たか？
    vector visited(H, vector<vector<bool>>(W, vector<bool>(4, false)));
    for(ll i=0; i<4; i++) visited[0][0][i] = true;

    // 拡張BFS
    deque<tuple<ll,ll>> deq; // (h,w)
    deq.push_back({0,0});
    while(!deq.empty()) {
        auto[h, w] = deq.front(); deq.pop_front();

        // 終了条件
        if (h==H-1 && w==W-1) {
            cout << "Yes" << endl;
            return;
        }

        // 次の探索
        for(ll vi=0; vi<4; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (!is_inside(nh,nw)) continue;
            if (mp[grid[h][w]] != grid[nh][nw]) continue;
            if (visited[nh][nw][vi]) continue;
            visited[nh][nw][vi] = true;
            deq.push_back({nh,nw});
        }
    }
    cout << "No" << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}