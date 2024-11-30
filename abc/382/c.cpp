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

#include <atcoder/lazysegtree>
using S = long long;
using F = long long;
const S INF = 8e18;
const F ID = 8e18;
S op(S l, S r){ return std::max(l, r); }
S e(){ return -2LL; }
S mapping(F f, S x){ return (f == ID ? x : f); }
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> B(M);
    vector<pair<ll,ll>> sushi(M); // (寿司の美味しさ,寿司id)
    for(ll i=0; i<M; i++) {
        cin >> B[i];
        sushi[i] = {B[i], i};
    }

    // 遅延セグメント木の作成
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(M+1);
    sort(sushi.begin(), sushi.end());
    for(ll i=N-1; i>=0; i--) {
        ll a = A[i];
        auto idx = lower_bound(sushi.begin(), sushi.end(), make_pair(a,-1LL)) - sushi.begin();
        if (idx == M) continue;
        seg.apply(idx, M+1, i);
    }

    // 答え
    vector<ll> ans(M, -1);
    for(ll i=0; i<M; i++) {
        auto[_, bi] = sushi[i];
        ll ai = seg.get(i);
        ans[bi] = ai;
    }

    for(ll i=0; i<M; i++) {
        cout << ans[i]+1 << endl;
    }
}

void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> B(M);
    priority_queue<pair<ll,ll>> sushi_pq; // (寿司の美味しさ,寿司id)
    for(ll i=0; i<M; i++) {
        cin >> B[i];
        sushi_pq.push({B[i], i});
    }

    // 人iから順に美味しさの大きい寿司を食べていく
    vector<ll> ans(M,-2);
    for(ll i=0; i<N; i++) {
        if (sushi_pq.empty()) break;

        auto[b, id] = sushi_pq.top();
        if (A[i] <= b) {
            sushi_pq.pop();
            ans[id] = i;
            i--;
            continue;
        }
    }

    // 答え
    for(ll i=0; i<M; i++) {
        cout << ans[i]+1 << endl;
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}