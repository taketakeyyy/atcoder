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
    vector<ll> Q(N);
    for(ll i=0; i<N; i++) {
        ll p; cin >> p;
        Q[p-1] = i+1;
    }

    for(ll i=0; i<N; i++) {
        cout << Q[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}