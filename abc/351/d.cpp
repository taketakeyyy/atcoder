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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) cin >> grid[i];

    auto is_inside = [&](ll i, ll j) {
        return i>=0 and i<H and j>=0 and j<W;
    };

    ll ans = 0;
    vector memo(H, vector(W, false));
    auto bfs = [&](ll si, ll sj) {
        if (memo[si][sj]) return;
        deque<pair<ll,ll>> deq;
        deq.push_back({si, sj});
        // vector visited(H, vector(W, false)); // 重すぎ？
        // visited[si][sj] = true;
        set<pair<ll,ll>> visited;
        visited.insert({si,sj});
        memo[si][sj] = true;
        ll total = 0;
        while(!deq.empty()) {
            auto[i, j] = deq.front(); deq.pop_front();
            total++;

            // 終了条件
            bool is_ok = true;
            for(ll vi=0; vi<4; vi++) {
                ll ni = i + vy[vi];
                ll nj = j + vx[vi];
                if (!is_inside(ni, nj)) continue;
                if (grid[ni][nj] == '#') {
                    is_ok = false; break;
                }
            }
            if (!is_ok) continue;

            // 次の探索
            for(ll vi=0; vi<4; vi++) {
                ll ni = i + vy[vi];
                ll nj = j + vx[vi];
                if (!is_inside(ni, nj)) continue;
                if (grid[ni][nj]=='#') continue;
                // if (visited[ni][nj]) continue;
                // visited[ni][nj] = true;
                if (visited.count({ni,nj})) continue;
                visited.insert({ni,nj});
                memo[ni][nj] = true;
                deq.push_back({ni,nj});
            }
        }
        chmax(ans, total);
    };

    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            if (grid[i][j]=='#') continue;
            if (memo[i][j]) continue;
            // 周囲4マスに磁石がある場合、自由度は1
            bool is_ok = true;
            for(ll vi=0; vi<4; vi++) {
                ll ni = i + vy[vi];
                ll nj = j + vx[vi];
                if (!is_inside(ni, nj)) continue;
                if (grid[ni][nj] == '#') {
                    memo[i][j] = true;
                    chmax(ans, 1LL);
                    is_ok = false;
                    break;
                }
            }
            if (!is_ok) continue;

            bfs(i,j);
        }
    }

    // 答え
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}