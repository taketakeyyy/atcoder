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


ll f(ll mid, ll A, ll D) {
    return A + (mid-1)*D;
}

void solve() {
    ll X, A, D, N; cin >> X >> A >> D >> N;

    // D < 0 のとき、にぶたんの判定が逆になってめんどいので、D > 0に正規化する
    if (D < 0) {
        A = f(N, A, D);
        D = -D;
    }

    ll mn = min(f(1, A, D), f(N, A, D));
    ll mx = max(f(1, A, D), f(N, A, D));
    if (X <= mn) {
        cout << mn - X << endl;
        return;
    }
    if (mx <= X) {
        cout << X - mx << endl;
        return;
    }

    // にぶたん
    // O(log N)
    ll l = 1, r = N;
    while(r-l > 1) {
        ll mid = (r+l)/2;
        if (f(mid, A, D) < X) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    ll ans = abs(f(l, A, D)-X);
    ans = min(ans, abs(f(r, A, D)-X));
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}