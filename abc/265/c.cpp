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


bool inside(ll h, ll w, ll H, ll W) {
    return (h>=0 && h<H && w>=0 && w<W);
}

void solve() {
    ll H, W; cin >> H >> W;
    vector<string> G(H);
    for(ll i=0; i<H; i++) {
        cin >> G[i];
    }

    set<pair<ll,ll>> visited;
    deque<pair<ll,ll>> que; que.push_back({0,0});
    while(!que.empty()) {
        auto[h,w] = que.front(); que.pop_front();

        if (visited.count({h,w})) {
            cout << "-1" << endl;
            return;
        }
        visited.insert({h,w});

        ll nh, nw;
        if (G[h][w] == 'U') {
            nh = h-1; nw = w;
        }
        if (G[h][w] == 'D') {
            nh = h+1; nw = w;
        }
        if (G[h][w] == 'L') {
            nh = h; nw = w-1;
        }
        if (G[h][w] == 'R') {
            nh = h; nw = w+1;
        }

        if (inside(nh, nw, H, W)) {
            que.push_back({nh, nw});
        }
        else {
            cout << h+1 << " " << w+1 << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}