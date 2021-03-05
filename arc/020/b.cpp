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


void solve () {
    ll N, C; cin >> N >> C;
    vector<ll> A(N);
    map<ll,ll> mp_even;
    map<ll,ll> mp_odd;
    rep(i, N) {
        cin >> A[i];
        if (i%2==0) {
            mp_even[A[i]]++;
        }
        else{
            mp_odd[A[i]]++;
        }
    }
    // 色が10種類だけなので、全探索
    ll ans = INF;
    for(ll i=1; i<=10; i++) {
        for(ll j=1; j<=10; j++) {
            if (i==j) continue;
            ans = min(ans, C*(N-mp_even[i]-mp_odd[j]));
        }
    }
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}