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
    vector<ll> A(N);
    unordered_map<ll,vector<ll>> idxs;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        idxs[A[i]].push_back(i);
    }

    // 値xが1個も含まれない区間の個数を数え上げて、引いていく
    ll ans = 0;
    for(auto[_, vec]: idxs) {
        ll total = ((1+N)*N)/2;
        ll l = -1;
        for(ll i: vec) {
            ll r = i;
            ll n = r-l-1;
            total -= ((1+n)*n)/2;
            l = r;
        }
        if (l != N-1) {
            ll r = N;
            ll n = r-l-1;
            total -= ((1+n)*n)/2;
        }
        ans += total;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}