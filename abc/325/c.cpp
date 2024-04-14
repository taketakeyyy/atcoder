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
vector<ll> vy = { -1, 0, 1, 0, -1, -1,  1, 1};
vector<ll> vx = { 0, 1, 0, -1, -1,  1, -1, 1 };


void solve() {
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }

    auto is_inside = [&](ll h, ll w) {
        return (h>=0 && h<H && w>=0 && w<W);
    };

    ll group_id = 0;
    vector done(H, vector<bool>(W, false));
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (grid[h][w] == '#' && !done[h][w]) {
                done[h][w] = true;
                group_id++;

                // 伝播していく
                deque<pair<ll,ll>> deq; deq.push_back({h, w});
                while(!deq.empty()) {
                    auto[h, w] = deq.front(); deq.pop_front();

                    for(ll vi=0; vi<8; vi++) {
                        ll nh = h + vy[vi];
                        ll nw = w + vx[vi];
                        if (!is_inside(nh,nw)) continue;
                        if (grid[nh][nw] == '#' && !done[nh][nw]) {
                            done[nh][nw] = true;
                            deq.push_back({nh, nw});
                        }
                    }
                }
            }
        }
    }

    cout << group_id << endl;
}


int main() {
    solve();
    return 0;
}