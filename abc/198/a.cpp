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

template<typename T>
T combination(T n, T r) {
    if (n < r) return 0;

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i);
        bunbo = bunbo*(i+1);
    }
    return bunsi/bunbo;
}

void solve() {
    ll N; cin >> N;
    if (N==1) {
        cout << 0 << endl;
        return;
    }

    N -= 2;
    ll ans = combination<ll>(N+1, 1);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}