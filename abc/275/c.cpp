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
    vector<string> grid(9);
    for(ll i=0; i<9; i++) {
        cin >> grid[i];
    }

    ll ans = 0;
    for(ll i=0; i<9; i++) {
        for(ll j=0; j<9; j++) {
            if (grid[i][j] != '#') continue;

            // 時計回りに正方形を探す
            for(ll n=1; n<9; n++) {
                if (j+n<9 && grid[i][j+n]=='#') {
                    if (i+n<9 && grid[i+n][j+n]=='#') {
                        if (i+n<9 && grid[i+n][j]=='#') {
                            ans++;
                        }
                    }
                }
            }

            // 時計回りにななめ
            for(ll n=1; n<9; n++) {
                for(ll m=1; m<9; m++) {
                    ll i2 = i+n; ll j2 = j+m;
                    if (i2<9 && j2<9 && grid[i2][j2]=='#') {
                        ll i3 = i2+m; ll j3 = j2-n;
                        if (i3<9 && j3>=0 && grid[i3][j3]=='#') {
                            ll i4 = i3-n; ll j4 = j3-m;
                            if (i4>=0 && j4>=0 && grid[i4][j4]=='#') {
                                ans++;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}