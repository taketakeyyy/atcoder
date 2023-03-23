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

#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>


void solve() {
    ll N, Q; cin >> N >> Q;

    // fenwick treeを作成
    atcoder::fenwick_tree<ll> fw(N);

    // 数列Aになるように、fenwick treeの各要素に値を足す
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        fw.add(i, a);
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 0) {
            ll p, x; cin >> p >> x;
            // A[p]にxを一点加算
            fw.add(p, x);
        }
        else {
            ll l, r; cin >> l >> r;
            // 数列Aの [l, r) の区間和を取得
            cout << fw.sum(l, r) << endl;
        }
    }
}

struct S{
    long long value;
    int size;
};
using F = long long;

S op(S l, S r){ return {l.value+r.value, l.size+r.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){ return {x.value + f*x.size, x.size}; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void solve2() {
    ll N, Q; cin >> N >> Q;
    vector<S> A(N);
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        A[i] = S{a, 1};
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 0) {
            ll p, x; cin >> p >> x;
            seg.apply(p, p+1, x);
        }
        else {
            ll l, r; cin >> l >> r;
            cout << seg.prod(l, r).value << endl;
        }
    }
}


int main() {
    solve();
    // solve2();
    return 0;
}