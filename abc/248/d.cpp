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
    // vector<ll> A(N+1);
    map<ll,vector<ll>> mp;
    for(ll i=1; i<N+1; i++) {
        ll a;
        cin >> a;
        mp[a].push_back(i);
    }


    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll l, r, x; cin >> l >> r >> x;

        if (mp.count(x)) {
            ll ri = upper_bound(mp[x].begin(), mp[x].end(), r) - mp[x].begin();
            ll li = upper_bound(mp[x].begin(), mp[x].end(), l-1) - mp[x].begin();
            cout << ri - li << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}