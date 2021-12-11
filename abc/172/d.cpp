#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    ll N; cin >> N;
    vector<ll> f(N+1, 1);
    f[0] = 0;

    // fを作る
    for(ll i=2; i<=N; i++) {
        f[i]++;
        for(ll j=2; i*j<=N; j++) {
            f[i*j]++;
        }
    }

    ll ans = 0;
    for(ll k=1; k<=N; k++) {
        ans += k*f[k];
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}