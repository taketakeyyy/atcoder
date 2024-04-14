#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
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

#include <atcoder/lazysegtree>

using S = long long;
using F = long long;
S op(S a, S b){ return a^b; }
S e(){ return 0LL; }
S mapping(F f, S x) { return f^x; }
F composition(F f, F g) { return f^g; }
F id() { return 0LL; }

void solve() {
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 遅延セグメント木作成
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    for(ll q=0; q<Q; q++) {
        ll t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            x--;
            seg.apply(x, x+1, y);
        }
        else {
            x--; y--;
            cout << seg.prod(x, y+1) << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}