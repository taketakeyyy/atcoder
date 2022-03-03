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
    ll X; cin >> X;
    if (0<=X && X<40) {
        cout << 40-X << endl;
    }
    else if (40<=X && X<70) {
        cout << 70-X << endl;
    }
    else if (70<=X && X<90) {
        cout << 90-X << endl;
    }
    else {
        cout << "expert" << endl;
    }
}


int main() {
    solve();
    return 0;
}