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
    ll N; cin >> N;
    vector<ll> A(N);
    ll Atotal = 0;
    ll t = A.size();
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        Atotal += A[i];
    }
    ll X; cin >> X;

    if (X <= Atotal) {
        ll ans = 0;
        ll total = 0;
        for(ll i=0; i<N; i++) {
            total += A[i];
            ans++;
            if (total > X) {
                cout << ans << endl;
                return;
            }
        }
    }
    else {
        ll ans = (X/Atotal)*t;
        ll rest = X%Atotal;
        ll i=0;
        while(rest >= 0) {
            rest -= A[i];
            i++;
            ans++;
        }
        cout << ans << endl;
        return;
    }
}


int main() {
    solve();
    return 0;
}