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
    map<ll, vector<pair<ll,ll>>> mp;
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        mp[y].push_back({x,i});
    }
    string S; cin >> S;

    for(auto [key, vec]: mp) {
        if (vec.size() <= 1) { continue; }

        // sort(vec.begin(), vec.end());

        ll l = INF;
        ll r = -INF;
        for(ll i=0; i<vec.size(); i++) {
            ll x, id;
            tie(x, id) = vec[i];

            if (S[id]=='R') {
                l = min(l, x);
            }
            else {
                r = max(r, x);
            }
        }

        if (l < r) {
            cout << "Yes" << endl;
            return;
        }
    }

    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}