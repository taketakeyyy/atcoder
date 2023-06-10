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
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }

    // 部分長方形の縦横の座標を測る
    ll mnW=INF, mxW=-1;
    ll mnH=INF, mxH=-1;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (grid[h][w] == '#') {
                mnW = min(mnW, w);
                mxW = max(mxW, w);
                mnH = min(mnH, h);
                mxH = max(mxH, h);
            }
        }
    }

    // 部分長方形から、クッキーがない箇所を探す
    for(ll h=mnH; h<=mxH; h++) {
        for(ll w=mnW; w<=mxW; w++) {
            if (grid[h][w] == '.') {
                cout << h+1 << " " << w+1 << endl;
                return;
            }
        }
    }

}


int main() {
    solve();
    return 0;
}