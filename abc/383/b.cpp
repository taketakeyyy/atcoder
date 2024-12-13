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
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }

    vector<pair<ll,ll>> floors;
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            if (grid[i][j] == '.') floors.push_back({i,j});
        }
    }

    // 座標(h,w)はグリッドの内側に収まっているか？
    auto is_inside = [&](const ll &h, const ll &w) -> bool {
        return h>=0 and h<H and w>=0 and w<W;
    };

    auto bfs = [&](ll n, set<pair<ll,ll>> &humidified) -> void {
        auto[sh, sw] = floors[n];
        deque<tuple<ll,ll,ll>> deq;
        deq.push_back({0,sh,sw});
        humidified.insert({sh,sw});
        set<pair<ll,ll>> visited;
        visited.insert({sh,sw});

        while(!deq.empty()) {
            auto[d,h,w] = deq.front(); deq.pop_front();

            // 終了条件
            if (d >= D) continue;

            // 次の探索
            for(ll vi=0; vi<4; vi++) {
                ll nh = h + vy[vi];
                ll nw = w + vx[vi];
                if (is_inside(nh,nw) == false) continue;
                if (visited.count({nh,nw})) continue;
                visited.insert({nh,nw});
                if (grid[nh][nw] == '.') humidified.insert({nh,nw});
                deq.push_back({d+1,nh,nw});
            }
        }

    };

    auto f = [&](ll n1, ll n2) -> ll {
        set<pair<ll,ll>> humidified; // 加湿された床
        bfs(n1, humidified);
        bfs(n2, humidified);
        return humidified.size();
    };

    // 加湿器を置く床を全探索
    ll ans = 0;
    ll FN = floors.size();
    for(ll i=0; i<FN; i++) {
        for(ll j=i+1; j<FN; j++) {
            chmax(ans, f(i,j));
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}