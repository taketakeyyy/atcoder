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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll A, B; cin >> A >> B;
    if  (A+B>=15 && B>=8) {
        cout << 1 << endl;
    }
    else if (A+B>=10 && B>=3) {
        cout << 2 << endl;
    }
    else if (A+B>=3) {
        cout << 3 << endl;
    }
    else {
        cout << 4 << endl;
    }
}


int main() {
    solve();
    return 0;
}