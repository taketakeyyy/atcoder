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
    ll N; cin >> N;
    vector<ll> A, B;
    for (ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        A.push_back(a);
        B.push_back(b);
    }

    // 全探索
    ll ans = INF;
    for(ll i=0; i<N; i++) {
        for (ll j=0; j<N; j++) {
            if (i==j) {
                ans = min(ans, A[i]+B[j]);
            }
            else {
                ans = min(ans, max(A[i], B[j]));
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}