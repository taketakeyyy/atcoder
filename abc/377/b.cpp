#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


void solve() {
    vector<string> grid(8);
    for(ll i=0; i<8; i++) cin >> grid[i];

    vector<bool> row(8, true), col(8, true);
    for(ll i=0; i<8; i++) {
        for(ll j=0; j<8; j++) {
            if (grid[i][j] == '#') {
                row[i] = false;
                col[j] = false;
            }
        }
    }

    ll ans = 0;
    for(ll i=0; i<8; i++) {
        for(ll j=0; j<8; j++) {
            if (row[i] and col[j]) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}