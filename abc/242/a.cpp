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
    ll A, B, C, X; cin >> A >> B >> C >> X;
    if (X <= A) {
        cout << "1" << endl;
    }
    else if ((A+1)<=X && X<=B){
        double ans = (double)C/(B-A);
        printf("%.6lf\n", ans);
    }
    else {
        cout << 0 << endl;
    }
}


int main() {
    solve();
    return 0;
}