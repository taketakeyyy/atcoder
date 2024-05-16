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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

#include <atcoder/lazysegtree>
// 区間加算・区間最大値
using S = long long;
using F = long long;
const S INF = 8e18;
S op(S l, S r){ return std::max(l, r); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void solve() {
    ll N, D, A; cin >> N >> D >> A;
    vector<pair<ll,ll>> enemy(N);
    vector<ll> X(N);
    for(ll i=0; i<N; i++) {
        ll x, h; cin >> x >> h;
        X[i] = x;
        enemy[i] = {x, h};
    }
    sort(enemy.begin(), enemy.end());
    sort(X.begin(), X.end());

    // 遅延セグメント木作成
    vector<S> B(N);
    for(ll i=0; i<N; i++) B[i] = enemy[i].second;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(B);

    // 爆発の左端ギリギリに生き残ってる敵が来るように、爆弾を貪欲に爆発させていく
    ll ans = 0;
    for(ll ei=0; ei<N; ei++) {
        if (seg.get(ei) <= 0) continue;
        ll x = enemy[ei].first+2*D; // 爆発の右端の座標
        ll idx = upper_bound(X.begin(), X.end(), x) - X.begin();
        ll cnt = intceil(seg.get(ei), A); // 爆発させる回数
        seg.apply(ei, idx, -A*cnt);
        ans += cnt;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}