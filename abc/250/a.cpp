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
    ll R, C; cin >> R >> C;
    ll ans = 0;
    if (R-1>=1) {
        ans++;
    }
    if (R+1<=H) {
        ans++;
    }
    if (C-1>=1) {
        ans++;
    }
    if (C+1<=W) {
        ans++;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}