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

ll A, B;

double f(ll m) {
    double t = (double)B*m;
    double g = 1+m;
    t += (double)A/sqrt(g);
    return t;
}

// 3分探索
void solve() {
    cin >> A >> B;

    ll left = 0;
    ll right = 1e18+100;
    ll cnt = 500;  // 適当
    double ans = f(0);
    while (cnt > 0) {
        cnt--;

        ll m1 = (2*left+right)/3;
        ll m2 = (left+2*right)/3;

        double ret1 = f(m1);
        double ret2 = f(m2);

        if (ret1 > ret2) {
            left = m1;
            ans = min(ans, ret2);
            continue;
        }
        else {
            right = m2;
            ans = min(ans, ret1);
            continue;
        }
    }

    printf("%.7lf\n", ans);
}


// 解説3分探索
void solve2() {
    cin >> A >> B;

    // 3分探索
    ll left = 0;
    ll right = A/B;
    while(right-left > 2) {
        ll m1 = (left*2+right)/3;
        ll m2 = (left+right*2)/3;

        if (f(m1)>f(m2)) left = m1;
        else right = m2;
    }

    // [left, right]が十分小さくなったので、最小値を探す
    double ans = A;
    for(ll i=left; i<=right; i++) {
        ans = min(ans, f(i));
    }

    // 出力
    printf("%.7lf\n", ans);
}

// 微分で解く
void solve3() {
    cin >> A >> B;

    // f(x)が最小となるxを求める
    ll argmin = pow((double)A/(2*B), 2.0/3.0) - 1;

    // 数値誤差が怖いので、余裕を持ってプラマイ5の範囲を調べる
    ll left = max(argmin-5, 0LL);
    ll right = argmin+5;
    double ans = A;
    for(ll i=left; i<=right; i++) {
        ans = min(ans, f(i));
    }

    // 出力
    cout << fixed << setprecision(7) << ans << endl;
}

int main() {
    solve3();
    return 0;
}