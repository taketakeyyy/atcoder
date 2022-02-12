#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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
    ll N; cin >> N;

    // 何桁の数字？
    ll d = 1;
    while (1) {
        if (N/d==0) break;
        d *= 10;
    }
    d /= 10;

    // 数え上げ
    ll ans = 0;
    if (d==1) {
        ans = (1+N)*(N)/2;
    }
    else {
        ll a = (1+N-d+1)%MOD;
        ll b = (N-d+1)%MOD;
        ans = a*b/2;
        ans %= MOD;
        while (1) {
            if (d==1) break;
            ll n = d-1-d/10+1;
            ll a = (1+n)%MOD;
            ll b = n%MOD;
            ans += a*b/2;
            ans %= MOD;
            d /= 10;
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}