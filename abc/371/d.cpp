#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1'000'000'007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> X(N);
    for(ll i=0; i<N; i++) cin >> X[i];
    vector<ll> P(N);
    for(ll i=0; i<N; i++) cin >> P[i];

    // 村を座標昇順にする
    vector<pair<ll,ll>> village(N+1, make_pair<ll>(-INF,0));
    for(ll i=1; i<=N; i++) village[i] = {X[i-1], P[i-1]};
    sort(village.begin(), village.end());

    // 累積和を作る
    vector<ll> S(N+1, 0LL);
    for(ll i=1; i<=N; i++) S[i] = S[i-1] + village[i].second;

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll l, r; cin >> l >> r;
        ll ldx = lower_bound(village.begin(), village.end(), make_pair(l, -INF)) - village.begin();
        ll rdx = upper_bound(village.begin(), village.end(), make_pair(r, INF)) - village.begin();
        ll ans = S[rdx-1] - S[ldx-1];
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}