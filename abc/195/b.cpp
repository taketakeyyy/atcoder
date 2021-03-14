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
    ll A, B, W; cin >> A >> B >> W;
    W *= 1000;
    ll n = W/A;
    ll mx = -1;
    if (A*n<=W && W<= B*n) {
        mx = n;
    }

    ll mn = -1;
    n = (W+(B-1))/B;
    if (A*n<=W && W<=B*n) {
        mn = n;
    }

    if (mn==-1 || mx==-1) {
        cout << "UNSATISFIABLE" << endl;
    }
    else {
        cout << mn << " " << mx << endl;
    }
}


int main() {
    solve();
    return 0;
}