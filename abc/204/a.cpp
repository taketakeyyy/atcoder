#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll x, y; cin >> x >> y;
    if (x==y) {
        cout << x << endl;
    }
    else {
        set<ll> sets;
        sets.insert(0); sets.insert(1); sets.insert(2);
        sets.erase(x); sets.erase(y);
        for (auto a: sets) {
            cout << a << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}