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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };



void solve() {
    ll R, C; cin >> R >> C;
    vector<string> grid(R);
    for(ll i=0; i<R; i++) {
        string line; cin >> line;
        grid[i] = line;
    }

    auto is_inside = [&](ll h, ll w) {
        return (h>=0 && h<R && w>=0 && w<C);
    };

    for(ll i=0; i<R; i++) {
        for(ll j=0; j<C; j++) {
            if (grid[i][j] == '.' || grid[i][j] == '#') continue;

            // BFSで爆発させる
            ll num = grid[i][j] - '0';
            grid[i][j] = '.';
            deque<tuple<ll,ll,ll>> deq;
            deq.push_back({i,j,num});
            set<pair<ll,ll>> visited;
            visited.insert({i,j});
            while(!deq.empty()) {
                auto[h, w, cnt] = deq.front(); deq.pop_front();
                for(ll vi=0; vi<4; vi++) {
                    ll nh = h + vy[vi];
                    ll nw = w + vx[vi];
                    if (!is_inside(nh, nw)) continue;
                    if (visited.count({nh,nw})) continue;
                    if (grid[nh][nw] == '#') grid[nh][nw] = '.';
                    if (cnt-1 == 0) continue;
                    deq.push_back({nh, nw, cnt-1});
                }
            }
        }
    }

    // 出力
    for(ll i=0; i<R; i++) {
        cout << grid[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}