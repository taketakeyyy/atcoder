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


void solve() {
    ll R, C; cin >> R >> C;
    ll sy, sx; cin >> sy >> sx; sy--; sx--;
    ll gy, gx; cin >> gy >> gx; gy--; gx--;
    vector<string> grid(R);
    for(ll i=0; i<R; i++) cin >> grid[i];

    // 上右下左
    const vector<ll> vy = { -1, 0, 1, 0 };
    const vector<ll> vx = { 0, 1, 0, -1 };

    // (y,x)座標がグリッド内に収まっているか？
    auto is_inside = [&](ll y, ll x) -> bool {
        return (y>=0 && y<R && x>=0 && x<C);
    };

    // BFS
    deque<tuple<ll,ll,ll>> deq;// (y,x,cost)
    deq.push_back({sy,sx,0});
    vector visited(R, vector<bool>(C, false)); // visited[y][x] := 座標(y,x)は訪問済みか？
    visited[sy][sx] = true;
    while(!deq.empty()) {
        auto[y, x, cost] = deq.front(); deq.pop_front();

        // 終了条件
        if (y==gy && x==gx) {
            cout << cost << endl;
            return;
        }

        // 次の探索
        for(ll vi=0; vi<4; vi++) {
            ll ny = y + vy[vi];
            ll nx = x + vx[vi];
            if (!is_inside(ny, nx)) continue;
            if (grid[ny][nx]!='.') continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = true;
            deq.push_back({ny,nx,cost+1});
        }
    }
}


int main() {
    solve();
    return 0;
}