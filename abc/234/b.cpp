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

    double ans = -INF;
    for(ll i=0; i<N; i++) {
        auto [x1, y1] = XY[i];
        for(ll j=i+1; j<N; j++) {
            auto [x2, y2] = XY[j];
            // 距離を計算
            double d = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            ans = max(ans, d);
        }
    }

    printf("%.7lf\n", ans);
}


int main() {
    solve();
    return 0;
}