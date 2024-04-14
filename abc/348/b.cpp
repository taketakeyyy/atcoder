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
    vector<ll> X(N), Y(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        X[i] = x;
        Y[i] = y;
    }

    auto f = [&](pair<ll,ll> p1, pair<ll,ll> p2) {
        auto[x1,y1] = p1;
        auto[x2, y2] = p2;
        return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    };

    for(ll i=0; i<N; i++) {
        ll mxd = 0;
        ll ans = -1;
        for(ll j=0; j<N; j++) {
            if (i==j) continue;
            ll d = f({X[i],Y[i]}, {X[j],Y[j]});
            if (d > mxd) {
                mxd = d;
                ans = j;
            }
        }
        cout << ans+1 << endl;
    }
}


int main() {
    solve();
    return 0;
}