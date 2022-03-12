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
    ll s, t; cin >> s >> t;

    ll ans = 0;
    for(ll a=0; a<=100; a++) {
        for(ll b=0; b<=100; b++) {
            for(ll c=0; c<=100; c++) {
                if ((a+b+c <= s) && (a*b*c <= t)) {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}