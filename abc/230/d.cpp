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


bool compare_func(pair<ll,ll> p1, pair<ll,ll> p2) {
    if (p1.second < p2.second) {
        return true;
    }
    if (p1.second == p2.second) {
        return (p1.first < p2.first);
    }
    return false;
}

void solve() {
    ll N, D; cin >> N >> D;
    vector<pair<ll,ll>> LR(N);
    for(ll i=0; i<N; i++) {
        ll l, r; cin >> l >> r;
        LR[i] = {l, r};
    }

    // Rでソートして区間スケジューリング的貪欲。
    sort(LR.begin(), LR.end(), compare_func);

    ll ans = 0;
    ll i = 0;
    while(1) {
        if (i >= (ll)LR.size()) break;

        auto [l, r] = LR[i];
        ll punch = r+D-1;
        i++;
        while(1) {
            if (i >= (ll)LR.size()) break;

            auto [l2, r2] = LR[i];
            if (l2 <= punch) {
                i++;
                continue;
            }
            break;
        }
        ans++;
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}