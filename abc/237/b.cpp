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
    for (ll h=0; h<H; h++) {
        for (ll w=0; w<W; w++) {
            ll a; cin >> a;
            A[h][w] = a;
        }
    }

    // 出力
    for (ll w=0; w<W; w++) {
        for (ll h=0; h<H; h++) {
            if (h != H-1) {
                cout << A[h][w] << " ";
            }
            else {
                cout << A[h][w] << endl;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}