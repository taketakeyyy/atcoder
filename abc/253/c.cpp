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
    ll Q; cin >> Q;
    map<ll,ll> S;
    set<ll> sets;

    for(ll q=0; q<Q; q++) {
        ll cmd;
        cin >> cmd;
        if (cmd == 1) {
            ll x; cin >> x;
            S[x] += 1;
            sets.insert(x);
        }
        else if (cmd == 2) {
            ll x, c; cin >> x >> c;
            S[x] -= min(c, S[x]);
            if (S[x] == 0) {
                sets.erase(x);
            }
        }
        else {
            // 最大値 - 最小値
            auto it1 = sets.begin();
            auto it2 = sets.end();
            it2--;
            cout << (*it2) - (*it1) << endl;;
        }
    }
}


int main() {
    solve();
    return 0;
}