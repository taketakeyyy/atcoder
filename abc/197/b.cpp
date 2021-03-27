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
    ll H, W, X, Y; cin >> H >> W >> X >> Y;
    X--; Y--;
    vector<string> grid(H);
    rep(i, H) cin >> grid[i];

    ll ans = 1;
    // 上方向
    for(int h=X-1; h>=0; h--) {
        if (grid[h][Y]=='#') break;
        ans ++;
    }
    for(int h=X+1; h<H; h++) {
        if (grid[h][Y]=='#') break;
        ans ++;
    }
    for(int w=Y-1; w>=0; w--) {
        if (grid[X][w]=='#') break;
        ans ++;
    }
    for(int w=Y+1; w<W; w++) {
        if (grid[X][w]=='#') break;
        ans ++;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}