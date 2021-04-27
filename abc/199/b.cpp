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
    ll l=-1, r=INF;
    vector<ll> A(N);
    for(int i=0; i<N; i++) {
        cin >> A[i];
        l = max(l, A[i]);
    }
    vector<ll> B(N);
    for(int i=0; i<N; i++) {
        cin >> B[i];
        r = min(r, B[i]);
    }

    cout << max<ll>(0, r-l+1) << endl;
}


int main() {
    solve();
    return 0;
}