#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
static const double pi = 3.141592653589793;

void solve() {
    double T; cin >> T;
    double L, X, Y; cin >> L >> X >> Y;
    ll Q; cin >> Q;

    for(ll q=0; q<Q; q++) {
        double e; cin >> e;
        double A; // 観覧車のZ軸方向の高さ
        A = (L/2)+(-L/2)*cos(2*pi*e/T);
        double y; // 観覧車のY座標
        y = -(L/2)*sin(2*pi*e/T);
        double B; // 観覧車からXY平面に伸ばした垂線の交点から、高橋像の点までの線分の長さ
        B = sqrt(pow(X-0, 2)+pow(Y-y, 2));
        if (B==0) {
            cout << 90 << endl;
        }
        else {
            double theta = atan2(A, B);
            printf("%.8lf\n", theta*(180/pi));
        }
    }
}


int main() {
    solve();
    return 0;
}