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


void solve() {
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) { cin >> grid[i]; }
    pair<ll,ll> S, G;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (grid[h][w] == 'S') { S = {h, w}; }
            if (grid[h][w] == 'G') { G = {h, w}; }
        }
    }

    // BFS
    vector<vector<ll>> distS(H, vector<ll>(W, -1));  // Sからの最短距離
    ll dh[4] = {-1, 0, 1, 0};
    ll dw[4] = {0, -1, 0, 1};
    deque<tuple<ll, ll,ll>> deq;  // {cost, h, w}
    deq.push_back({0, S.first, S.second});
    while(!deq.empty()) {
        auto[cost, h, w] = deq.front(); deq.pop_front();

        for(ll i=0; i<4; i++) {
            ll nh = h + dh[i];
            ll nw = w + dw[i];
            if (nh<0 || nh>=H || nw<0 || nw>=W) { continue; }
            if (distS[nh][nw] != -1) { continue; }

            distS[nh][nw] = cost + 1;
            if (grid[nh][nw] == '.') {
                deq.push_back({cost+1, nh, nw});
            }
        }
    }

    // BFS
    vector<vector<ll>> distG(H, vector<ll>(W, -1));  // Gからの最短距離
    deq.clear();
    deq.push_back({0, G.first, G.second});
    while(!deq.empty()) {
        auto[cost, h, w] = deq.front(); deq.pop_front();

        for(ll i=0; i<4; i++) {
            ll nh = h + dh[i];
            ll nw = w + dw[i];
            if (nh<0 || nh>=H || nw<0 || nw>=W) { continue; }
            if (distG[nh][nw] != -1) { continue; }

            distG[nh][nw] = cost + 1;
            if (grid[nh][nw] == '.') {
                deq.push_back({cost+1, nh, nw});
            }
        }
    }

    // distS と distGの足しあわせて最大のマスが答え
    ll ans = 0;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (distS[h][w]==-1 || distG[h][w]==-1) { continue; }
            ans = max(ans, distS[h][w]+distG[h][w]);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}