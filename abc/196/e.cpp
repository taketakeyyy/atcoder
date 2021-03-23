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
    // (t=1)x+aの関数が来るとy切片が上下に動き、
    // (t=2)maxの関数が来ると最大値が更新され、
    // (t=3)minの関数が来ると最小値が更新される
    ll N; cin >> N;
    ll mn=-INF, mx=INF;
    ll s = 0;  // aの合計(y切片)
    for(int i=0; i<N; i++) {
        ll a, t; cin >> a >> t;
        if (t==1) {
            s += a;
            mn += a;
            mx += a;
        }
        else if (t==2) {
            mn = max(mn, a);
            mx = max(mx, a);
        }
        else {
            mn = min(mn, a);
            mx = min(mx, a);
        }
    }

    ll Q; cin >> Q;
    for(int q=0; q<Q; q++) {
        ll x; cin >> x;
        ll ans = x+s;
        if (ans < mn) ans = mn;
        if (ans > mx) ans = mx;
        cout << ans << endl;
    }

}


int main() {
    solve();
    return 0;
}