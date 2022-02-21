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
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    set<pair<ll,ll>> sets1;
    sets1.insert({x1-1, y1+2});
    sets1.insert({x1-2, y1+1});
    sets1.insert({x1-2, y1-1});
    sets1.insert({x1-1, y1-2});
    sets1.insert({x1+1, y1-2});
    sets1.insert({x1+2, y1-1});
    sets1.insert({x1+2, y1+1});
    sets1.insert({x1+1, y1+2});

    set<pair<ll,ll>> sets2;
    sets2.insert({x2-1, y2+2});
    sets2.insert({x2-2, y2+1});
    sets2.insert({x2-2, y2-1});
    sets2.insert({x2-1, y2-2});
    sets2.insert({x2+1, y2-2});
    sets2.insert({x2+2, y2-1});
    sets2.insert({x2+2, y2+1});
    sets2.insert({x2+1, y2+2});

    for (auto p: sets1) {
        if (sets2.count(p)) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
    return;
}


int main() {
    solve();
    return 0;
}