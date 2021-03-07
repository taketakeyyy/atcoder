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
    // 隣り合う2項はm-1通りある
    // 2項(a,b)のa,bの絶対値の差がdである確率を求めて、(m-1)倍すればよい
    ll n, m, d; cin >> n >> m >> d;
    double ans;
    if (d==0) {
        // (1,1),...(n,n)のn通り
        ans = (double)n/pow(n,2);
        ans *= (m-1);
    }
    else {
        // (1, 1+d), (2, 2+d), ..., (n-d, n)
        // (1+d, 1), (2+d, 2), ..., (n, n-d) の2(n-d)通り
        ans = (double)2*(n-d)/pow(n,2);
        ans *= (m-1);
    }
    printf("%.10lf", ans);
}


int main() {
    solve();
    return 0;
}