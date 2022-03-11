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
    // 左下の頂点と、右上の頂点が定まれば、四角形が作れるかどうかがわかる
    ll N; cin >> N;
    vector<pair<ll,ll>> coords(N);
    set<pair<ll,ll>> coordsets;
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        coordsets.insert({x,y});
        coords[i] = {x,y};
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ll x1, y1;
        tie(x1, y1) = coords[i];

        for(ll j=i+1; j<N; j++) {
            ll x2, y2;
            tie(x2, y2) = coords[j];

            if (x1==x2 || y1==y2) continue;

            if (coordsets.count({x1,y2}) && coordsets.count({x2,y1})) {
                ans++;
            }
        }
    }

    cout << ans/2 << endl;  // 2倍重複して数えるので
}


int main() {
    solve();
    return 0;
}