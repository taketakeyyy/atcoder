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


// ただの貪欲です
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> P(N);
    multiset<ll> msP;
    for(ll i=0; i<N; i++) {
        cin >> P[i];
        msP.insert(P[i]);
    }
    vector<ll> L(M), D(M);
    for(ll i=0; i<M; i++) cin >> L[i];
    for(ll i=0; i<M; i++) cin >> D[i];

    // クーポンを割引額が大きい順にソートする
    vector<pair<ll,ll>> coupons(M);
    for(ll i=0; i<M; i++) {
        coupons[i] = {D[i], L[i]};
    }
    sort(coupons.begin(), coupons.end());
    reverse(coupons.begin(), coupons.end());

    // 貪欲に割引額が大きいクーポンから試す
    ll ans = accumulate(P.begin(), P.end(), 0LL);
    for(ll i=0; i<M; i++) {
        auto[d, l] = coupons[i];
        auto it = msP.lower_bound(l);
        if (it == msP.end()) continue;
        msP.erase(it);
        ans -= d;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}