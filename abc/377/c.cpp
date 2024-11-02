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
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

vector<ll> vy = { -1, -2, -2, -1, 1, 2, 2, 1 };
vector<ll> vx = { -2, -1, 1, 2, -2, -1, 1, 2 };

// 置けないところを数え上げる
void solve() {
    ll N, M; cin >> N >> M;

    // 座標(h,w)はグリッドの内側に収まっているか？
    auto is_inside = [&](const ll &h, const ll &w) -> bool {
        return h>=0 and h<N and w>=0 and w<N;
    };

    set<pair<ll,ll>> unput; // 置けないところ
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        unput.insert({a,b});
        for(ll vi=0; vi<8; vi++) {
            ll na = a + vy[vi];
            ll nb = b + vx[vi];
            if (is_inside(na, nb) == false) continue;
            unput.insert({na,nb});
        }
    }

    ll ans = N*N - (ll)unput.size();
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}