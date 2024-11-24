#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
// const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
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

#include <atcoder/lazysegtree>
using S = long long;
using F = long long;
const S INF = 0;
S op(S l, S r){ return std::min(l, r); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void solve() {
    // 遅延セグメント木作成
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(2e5+10);
    ll l=0,r=0;
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll type; cin >> type;
        if (type == 1) {
            // 植える
            r++;
            continue;
        }
        if (type == 2) {
            // T日松
            ll T; cin >> T;
            if (l==r) continue;
            seg.apply(l, r, T);
            continue;
        }
        if (type == 3) {
            // 収穫
            ll H; cin >> H;
            ll ans = 0;
            // cout << "==DEBUG==" << endl;
            // for(ll i=0; i<3; i++) {
            //     cout << seg.get(i) << " ";
            // }
            // cout << endl;
            // cout << "==END==" << endl;
            while(l != r) {
                ll h = seg.get(l);
                if (h >= H) {
                    ans++;
                    l++;
                    continue;
                }
                break;
            }
            cout << ans << endl;
            continue;
        }
    }
}


int main() {
    solve();
    return 0;
}