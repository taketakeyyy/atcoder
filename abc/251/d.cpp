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
    ll W; cin >> W;
    // 99|99|99 を表現したい
    // 1, 2, ..., 99
    // 100, 200, ..., 9900
    // 10000, 20000, 990000
    // 99*3 = 297個でできる
    cout << 297 << endl;
    for(ll i=1; i<=99; i++) {
        cout << i << " ";
    }
    for(ll i=100; i<=9900; i+=100) {
        cout << i << " ";
    }
    for(ll i=10000; i<=990000; i+=10000) {
        cout << i << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}