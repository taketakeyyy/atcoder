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
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }

// 区間更新・区間最小値
#include <atcoder/lazysegtree>
using S = long long;
using F = long long;
const S INF = 8e18;
const F ID = 8e18;
S op(S l, S r){ return std::min(l, r); }
S e(){ return INF; }
S mapping(F f, S x){ return (f == ID ? x : f); }
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

void solve() {
    ll H, W, N; cin >> H >> W >> N;
    vector<tuple<ll,ll,ll,ll>> bar(N); // (r,c,l,バーid)
    for(ll i=0; i<N; i++) {
        ll r, c, l; cin >> r >> c >> l;
        r--; c--;
        bar[i] = {r,c,l,i};
    }

    // 下のバーから順番に処理する
    sort(bar.begin(), bar.end());
    reverse(bar.begin(), bar.end());
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> W2H(W+1); // W2H[w] := w列の、バーを置ける高さ
    W2H.apply(0, W, H-1);
    vector<ll> ans(N);
    for(ll i=0; i<N; i++) {
        auto[r,c,l,id] = bar[i];

        ll mnH = W2H.prod(c,c+l);
        ans[id] = mnH;
        W2H.apply(c,c+l,mnH-1);
    }

    // 答え
    for(ll i=0; i<N; i++) {
        cout << ans[i]+1 << endl;
    }
}


int main() {
    solve();
    return 0;
}