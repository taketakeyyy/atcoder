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


void solve() {
    ll N; cin >> N;
    vector<pair<ll,ll>> XY(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        XY[i] = {x,y};
    }

    set<pair<ll,ll>> learned;
    ll ans = 0;
    for(ll i=0; i<N-1; i++) {
        ll x1 = XY[i].first;
        ll y1 = XY[i].second;
        for(ll j=i+1; j<N; j++) {
            ll x2 = XY[j].first;
            ll y2 = XY[j].second;

            ll dx = x1-x2;
            ll dy = y1-y2;
            ll cd = gcd(dx, dy);
            if (!learned.count({dx/cd, dy/cd})) {
                learned.insert({dx/cd, dy/cd});
                ans++;
            }
            if (!learned.count({-dx/cd, -dy/cd})) {
                learned.insert({-dx/cd, -dy/cd});
                ans++;
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}