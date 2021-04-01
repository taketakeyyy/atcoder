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
    ll N; cin >> N;
    map<ll,ll> mp;

    for(ll j=1; j<=N; j++) {
        ll n = j;
        ll i = 2;
        while (n!=1) {
            while(n%i==0) {
                mp[i]++;
                n /= i;
            }
            i++;
        }
    }

    ll ans = 1;
    for(auto [p,q]: mp) {
        ans *= (q+1);
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}