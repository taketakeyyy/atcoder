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
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];
    // ソートして貪欲でOK
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ans += abs(A[i]-B[i]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}