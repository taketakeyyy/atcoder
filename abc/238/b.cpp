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
    vector<ll> kirikomi;
    kirikomi.push_back(0);
    ll top = 0;
    for (ll i=0; i<N; i++) {
        ll a; cin >> a;
        ll tmp = top - a;
        if (tmp < 0) tmp += 360;
        kirikomi.push_back(tmp);
        top = tmp;
    }

    sort(kirikomi.begin(), kirikomi.end());
    ll ans = -1;
    for (ll i=1; i<kirikomi.size(); i++) {
        ans = max(ans, kirikomi[i] - kirikomi[i-1]);
    }
    ans = max(ans, 360-kirikomi[kirikomi.size()-1]);

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}