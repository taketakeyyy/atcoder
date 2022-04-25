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


ll f(ll a, ll b) {
    return a*a*a + a*a*b + a*b*b + b*b*b;
}

void solve() {
    ll N; cin >> N;

    ll X = INF;
    for(ll a=0; a<=1000000; a++) {
        // にぶたんでbを探索
        ll l = 0;
        ll r = 1000000;
        while(r-l > 1) {
            ll b = (l+r)/2;
            if (f(a, b) >= N) {
                r = b;
                continue;
            }
            else {
                l = b;
                continue;
            }
        }
        if (f(a, l) >= N) {
            X = min(X, f(a, l));
        }
        else {
            X = min(X, f(a, r));
        }
    }

    // 出力
    cout << X << endl;
}


int main() {
    solve();
    return 0;
}