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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

ll A, B, C;
double f(double t) {
    return (double)A*t + (double)B * sin(C*t*M_PI);
}

// 二分探索でtを求める
void solve() {
    cin >> A >> B >> C;

    double l=0.0, r=1e18;
    ll cnt = 100000;  // 適当な回数やる
    while(cnt-- != 0) {
        double mid = (r+l)/2.0;
        if (abs(f(mid)-100) <= 0.000001) break;  // 十分相対誤差が小さくなってもOK

        if (f(mid) >= 100) r = mid;
        else l = mid;
    }
    double mid = (r+l)/2.0;
    printf("%.15lf\n", mid);  // なるべく厳密に出したい
}


int main() {
    solve();
    return 0;
}