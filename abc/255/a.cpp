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
    ll R, C; cin >> R >> C;
    R--; C--;
    vector<vector<ll>> A(2, vector<ll>(2, 0));
    for(ll i=0; i<2; i++) {
        for(ll j=0; j<2; j++) {
            cin >> A[i][j];
        }
    }

    cout << A[R][C] << endl;
}


int main() {
    solve();
    return 0;
}