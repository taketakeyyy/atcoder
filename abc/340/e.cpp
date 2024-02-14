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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

#include <atcoder/lazysegtree>
using S = long long;
using F = long long;
S op(S l, S r){ return std::min(l, r); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> B(M+1);
    for(ll i=1; i<=M; i++) cin >> B[i];

    // 遅延セグメント木作成
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    for(ll i=1; i<=M; i++) {
        ll ball = seg.get(B[i]);
        ll lap = ball/N;
        ll amari = ball%N;
        seg.set(B[i], 0);
        seg.apply(0, N, lap);

        // あまり処理
        ll rcnt = N-B[i]-1;
        if (rcnt <= amari) {
            seg.apply(B[i]+1, N, 1);
            amari -= rcnt;
            seg.apply(0, amari, 1);
        }
        else {
            seg.apply(B[i]+1, B[i]+1+amari, 1);
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << seg.get(i) << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}