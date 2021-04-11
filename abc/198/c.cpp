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
    ll R, X, Y; cin >> R >> X >> Y;
    ll r2 = X*X+Y*Y;
    ll R2 = R*R;

    if (r2 < R2) {
        cout << 2 << endl;
        return;
    }

    // 答えは切り上げ
    ll ans = intceil(r2, R2);
    ans = ceil(sqrt(ans));
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}