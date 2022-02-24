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
    ll ra, rb; cin >> ra >> rb;
    ll u, v; cin >> u >> v;
    ll root;
    if (ra == u) {
        root = u;
    }
    else if (ra == v) {
        root = v;
    }
    else if (rb == u) {
        root = u;
    }
    else if (rb == v) {
        root = v;
    }
    else {
        cout << "No" << endl;
        return;
    }
    bool is_star = true;
    for(ll i=2; i<N-1; i++) {
        cin >> u >> v;
        if (root == u || root == v) {
            continue;
        }
        else {
            is_star = false;
            break;
        }
    }

    if (is_star) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}