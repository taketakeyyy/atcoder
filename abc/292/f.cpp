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

// 弧度法をラジアンに直す
long double rad(long double x) {
    return x * M_PI / 180.;
}

bool f(double theta, double A, double B) {
    return (A/cos(rad(theta)) - B/cos(rad(30-theta)) >= 0);
}

// 解説AC
void solve() {
    ll A, B; cin >> A >> B;
    if (A > B) swap(A, B);

    {//正三角形の一辺が、長方形の一辺につけれる場合
        double x = (double)A/cos(rad(30));
        if (x <= B) {
            printf("%.10lf\n", x);
            return;
        }
    }

    {// それ以外の場合、θを二分探索で求める
        double l=0., r=30.;
        ll cnt = 1e6;  // 適当回数
        while(cnt-- >= 0) {
            double theta = (l+r)/2.;
            if (f(theta, A, B)) r = theta;
            else l = theta;
        }
        double theta = (l+r)/2.;
        double ans = (double)A/cos(rad(theta));
        printf("%.10lf\n", ans);
    }
}

// 解説AC
// 式変形をして形式的に求める方法
void solve2() {
    ll A, B; cin >> A >> B;
    if (A > B) swap(A, B);

    {//正三角形の一辺が、長方形の一辺につけれる場合
        double x = (double)A/cos(rad(30));
        if (x <= B) {
            printf("%.10lf\n", x);
            return;
        }
    }

    {// それ以外の場合、θを形式的に求める
        double theta = atan(2.0*B/A-sqrt(3));
        double x = (double)A/cos(theta);
        printf("%.10lf\n", x);
    }
}

int main() {
    // solve();
    solve2();
    return 0;
}