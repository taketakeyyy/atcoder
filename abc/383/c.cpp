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
    ll H, W, D; cin >> H >> W >> D;
    vector<string> grid(H);
    for(ll h=0; h<H; h++) {
        cin >> grid[h];
    }

    vector humidified(H, vector<bool>(W, false));

    // 座標(h,w)はグリッドの内側に収まっているか？
    auto is_inside = [&](const ll &h, const ll &w) -> bool {
        return h>=0 and h<H and w>=0 and w<W;
    };

    vector<pair<ll,ll>> starts;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (grid[h][w] == 'H') {
                starts.push_back({h,w});
            }
        }
    }

    auto f = [&]() -> void {
        vector visited(H, vector<bool>(W, false));
        deque<tuple<ll,ll,ll>> deq;
        for(ll i=0; i<(ll)starts.size(); i++) {
            auto[sh,sw] = starts[i];
            deq.push_back({0,sh,sw});
            humidified[sh][sw] = true;
            visited[sh][sw] = true;
        }

        while(!deq.empty()) {
            auto[d, h, w] = deq.front(); deq.pop_front();

            // 終了条件
            if (d >= D) continue;

            // 次の探索
            for(ll vi=0; vi<4; vi++) {
                ll nh = h + vy[vi];
                ll nw = w + vx[vi];
                ll nd = d + 1;
                if (is_inside(nh,nw) == false) continue;
                if (grid[nh][nw] == '#') continue;
                if (visited[nh][nw]) continue;
                visited[nh][nw] = true;
                humidified[nh][nw] = true;
                deq.push_back({nd,nh,nw});
            }
        }
    };
    f();

    // 答え
    ll ans = 0;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (humidified[h][w]) ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}