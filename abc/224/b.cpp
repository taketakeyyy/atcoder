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
    ll H, W; cin >> H >> W;
    vector<vector<ll>> A(H, vector<ll>(W));
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            cin >> A[h][w];
        }
    }

    for(ll i1=0; i1<H-1; i1++) {
        for(ll i2=i1+1; i2<H; i2++) {
            for(ll j1=0; j1<W-1; j1++) {
                for(ll j2=j1+1; j2<W; j2++) {
                    if (!(A[i1][j1]+A[i2][j2] <= A[i2][j1]+A[i1][j2])) {
                        cout << "No" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "Yes" <<endl;
}


int main() {
    solve();
    return 0;
}