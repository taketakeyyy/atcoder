#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    ll N, W; cin >> N >> W;
    vector<pair<ll,ll>> AB(N);
    for(ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        AB[i] = {a,b};
    }

    // 1gあたりの美味しさが大きいチーズを貪欲に使う
    sort(AB.begin(), AB.end());

    ll ans = 0;
    ll wsum = 0;
    for(ll i=N-1; i>=0; i--) {
        auto [a, b] = AB[i];
        if (wsum + b <= W) {
            wsum += b;
            ans += a*b;
        }
        else {
            ans += a*(W-wsum);
            break;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}