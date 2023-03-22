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

#include <atcoder/lazysegtree>
#include <atcoder/modint>
using mint = atcoder::modint998244353;
struct S {
    mint value;
    int size;
};
struct F {
    mint b, c;
};
S op(S l, S r) { return S{l.value + r.value, l.size + r.size}; }
S e() { return S{0, 0}; }
S mapping(F f, S x) { return S{x.value * f.b + x.size * f.c, x.size}; }
F composition(F f, F g) { return F{g.b * f.b, g.c * f.b + f.c}; }
F id() { return F{1, 0}; }

void solve() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    // 数列Aの初期化
    vector<S> A(N);
    for (int i = 0; i < N; i++) {
        int x; scanf("%d", &x);
        A[i] = S{x, 1}; // (初期値, サイズ)
    }

    // 遅延セグメント木の作成
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    // クエリ処理
    for (int q = 0; q < Q; q++) {
        int query; cin >> query;
        if (query == 0) {
            int l, r, b, c; scanf("%d %d %d %d", &l, &r, &b, &c);
            // [l, r)を a = b*a+c で更新する
            seg.apply(l, r, F{b, c});
        } else {
            int l, r; scanf("%d %d", &l, &r);
            // [l, r)の区間和を出力する
            cout << seg.prod(l, r).value.val() << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}