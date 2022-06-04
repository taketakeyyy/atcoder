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
    vector<vector<ll>> A(N);
    for(ll i=0; i<N; i++) {
        A[i].resize(i+1);
        for(ll j=0; j<=i; j++) {
            if (j==0 || j==i) {
                A[i][j] = 1;
            }
            else {
                A[i][j] = A[i-1][j-1] + A[i-1][j];
            }
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<=i; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}