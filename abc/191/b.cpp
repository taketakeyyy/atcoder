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
    ll N, X; cin >> N >> X;
    vector<ll> As;
    rep(i,N) {
        ll a; cin >> a;
        if (a!=X) {
            As.push_back(a);
        }
    }

    for(int i=0; i<As.size(); i++) {
        cout << As[i];
        if (i!=As.size()-1) {
            cout << " ";
        }
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}