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
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll H, W, X, Y; cin >> H >> W >> X >> Y;
    X--; Y--;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }
    string T; cin >> T;

    // 座標(h,w)はグリッドの内側に収まっているか？
    auto is_inside = [&](const ll &h, const ll &w) -> bool {
        return h>=0 and h<H and w>=0 and w<W;
    };

    set<pair<ll,ll>> visited;
    ll h = X;
    ll w = Y;
    for(char c: T) {
        if (c == 'U') {
            if (is_inside(h-1, w) == false) continue;
            if (grid[h-1][w] == '#') continue;
            h--;
        }
        else if (c == 'D') {
            if (is_inside(h+1, w) == false) continue;
            if (grid[h+1][w] == '#') continue;
            h++;
        }
        else if (c == 'L') {
            if (is_inside(h, w-1) == false) continue;
            if (grid[h][w-1] == '#') continue;
            w--;
        }
        else if (c == 'R') {
            if (is_inside(h, w+1) == false) continue;
            if (grid[h][w+1] == '#') continue;
            w++;
        }
        if (grid[h][w] == '@') visited.insert({h,w});
    }

    cout << h+1 << " " << w+1 << " " << visited.size() << endl;
}


int main() {
    solve();
    return 0;
}