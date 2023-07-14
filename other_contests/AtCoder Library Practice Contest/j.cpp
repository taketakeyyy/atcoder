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

#include <atcoder/segtree>
using S = long long;
S op(S a, S b) { return max(a, b); }
S e() { return -1; }
S target;
bool comp(S x) { return x < target; }

void solve() {
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // セグメントツリー作成
    atcoder::segtree<S, op, e> seg(A);

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll t; cin >> t;
        if (t == 1) {
            ll x, v; cin >> x >> v;
            x--;
            // 一点更新：A[x] = v
            seg.set(x, v);
        }
        else if (t == 2) {
            ll l, r; cin >> l >> r;
            l--; r--;
            // 区間クエリ：max(A[l],...,A[r])
            cout << seg.prod(l, r+1) << endl;
        }
        else {
            ll x; cin >> x >> target;
            x--;
            // 二分探索クエリ：x​ ≤ j ≤ N, target​ ≤ A[j] ​を満たす最小の j
            cout << seg.max_right<comp>(x) + 1 << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}