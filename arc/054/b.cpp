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


// f'(x)=0のときf(x)は最小となるので、f'(x)=0となるxを探す。
void solve() {
    double P; cin >> P;

    // f(x)
    auto f = [&P](double x) {
        return x + P/pow(2, x/1.5);
    };

    // f'(x)
    auto fd = [&P](double x) {
        return 1 + P*log(pow(2, -1.0/1.5)) * pow(2, -x/1.5);
    };

    // 二分法（二分探索）
    double left = 0;
    double right = P;
    ll cnt = 500;  // 二分法の回数（適当）
    while(cnt-- > 0) {
        double mid = (left+right)/2;
        if (fd(mid) <= 0) left = mid;
        else right = mid;
    }

    // 出力
    printf("%.8lf\n", f(left));
}


int main() {
    solve();
    return 0;
}