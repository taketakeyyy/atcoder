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
    // 累積和で解く
    vector<vector<ll>> cls(2, vector<ll>(N+1, 0));
    for(int i=0; i<N; i++) {
        ll c, p; cin >> c >> p;
        if (c==1) {
            cls[0][i+1] = cls[0][i] + p;
            cls[1][i+1] = cls[1][i];
        }
        else {
            cls[0][i+1] = cls[0][i];
            cls[1][i+1] = cls[1][i] + p;
        }
    }

    // クエリに応答する
    ll Q; cin >> Q;
    for(int q=0; q<Q; q++) {
        ll l, r; cin >> l >> r;
        cout << cls[0][r]-cls[0][l-1] << " " << cls[1][r]-cls[1][l-1] << endl;
    }
}


int main() {
    solve();
    return 0;
}