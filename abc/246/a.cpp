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
    ll x1, y1; cin >> x1 >> y1;
    ll x2, y2; cin >> x2 >> y2;
    ll x3, y3; cin >> x3 >> y3;
    ll x4, y4;

    if (x1 == x2) x4 = x3;
    if (x2 == x3) x4 = x1;
    if (x3 == x1) x4 = x2;

    if (y1 == y2) y4 = y3;
    if (y2 == y3) y4 = y1;
    if (y3 == y1) y4 = y2;

    cout << x4 << " " << y4 << endl;
}


int main() {
    solve();
    return 0;
}