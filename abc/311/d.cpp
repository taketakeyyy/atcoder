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
    ll N, M; cin >> N >> M;
    vector<string> grid(N);
    for(ll i=0; i<N; i++) cin >> grid[i];

    vector touch(N, vector<bool>(M, false));
    touch[1][1] = true;

    vector visited(N, vector<bool>(M, false));
    visited[1][1] = true;
    vector memo(N, vector<bool>(M, false));
    auto dfs = [&](auto self, ll h, ll w, vector<vector<bool>>& visited) -> void {
        if (memo[h][w]) return;
        memo[h][w] = true;

        // 4方向どちらに移動できるか
        for(ll vi=0; vi<4; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (grid[nh][nw] == '#') continue;
            // 氷ならすべっていく
            while(grid[nh][nw] == '.') {
                touch[nh][nw] = true;
                nh += vy[vi];
                nw += vx[vi];
            }
            nh -= vy[vi];
            nw -= vx[vi];
            if (visited[nh][nw]) continue;
            visited[nh][nw] = true;
            self(self, nh, nw, visited);
            visited[nh][nw] = false;
        }
        return;
    };
    dfs(dfs, 1, 1, visited);

    // 答え
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<M; j++) {
            if (touch[i][j]) ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}