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
    ll L1, R1, L2, R2; cin >> L1 >> R1 >> L2 >> R2;
    vector<ll> A(104, 0);
    for(ll i=L1; i<=R1; i++) A[i]++;
    for(ll i=L2; i<=R2; i++) A[i]++;
    ll ans = 0;
    for(ll i=0; i<(ll)A.size(); i++) {
        if (A[i]==2) ans++;
    }
    ans = max(ans-1, 0LL);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}