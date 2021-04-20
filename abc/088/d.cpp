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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(int h=0; h<H; h++) {
        cin >> grid[h];
    }

    set<pair<ll,ll>> visited;
    visited.insert(make_pair(0,0));
    deque<tuple<ll,ll,ll>> deq;
    deq.push_back(make_tuple(0,0,0));
    ll ans_cost = -1;
    while(deq.size()!=0) {
        ll h, w, cost;
        tie(h,w,cost) = deq.front(); deq.pop_front();

        if (h==H-1 && w==W-1) {
            ans_cost = cost;
            break;
        }

        vector<pair<ll,ll>> nxs;
        nxs.push_back(make_pair(h-1, w));
        nxs.push_back(make_pair(h+1, w));
        nxs.push_back(make_pair(h, w-1));
        nxs.push_back(make_pair(h, w+1));
        for(auto[nh, nw] : nxs) {
            if (nh<0 || nh>=H || nw<0 || nw>=W) continue;
            if (grid[nh][nw]=='#') continue;
            if (visited.count(make_pair(nh,nw))) continue;
            deq.push_back(make_tuple(nh,nw,cost+1));
            visited.insert(make_pair(nh,nw));
        }
    }

    if (ans_cost==-1) {
        cout << -1 << endl;
        return;
    }

    // 白のタイルの数を数える
    ll white = 0;
    for(int h=0; h<H; h++) {
        for (int w=0; w<W; w++) {
            if (grid[h][w]=='.') white++;
        }
    }
    cout << white - 2 - (ans_cost-1) << endl;
}


int main() {
    solve();
    return 0;
}