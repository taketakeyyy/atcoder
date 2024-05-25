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


void solve() {
    ll N; cin >> N;
    vector<pair<ll,ll>> LR(N);
    vector<ll> L(N);
    for(ll i=0; i<N; i++) {
        ll l, r; cin >> l >> r;
        LR[i] = {l,r};
        L[i] = l;
    }

    // LRはrでソートする
    auto comp = [&](const pair<ll,ll> &p1, const pair<ll,ll> &p2) -> bool {
        return p1.second < p2.second;
    };
    sort(LR.begin(), LR.end(), comp);

    // Lはそのままソート
    sort(L.begin(), L.end());

    // 区間が重ならない組を数え上げる
    ll cnt = 0;
    for(ll i=0; i<N; i++) {
        auto[l, r] = LR[i];
        ll idx = upper_bound(L.begin(), L.end(), r) - L.begin();
        cnt += N - idx;
    }

    // 余事象が答え
    ll ans = (N*(N-1LL))/2LL - cnt;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}