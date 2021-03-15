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
    // (1) 1周期でどちらかが追い越せなかったら、永遠に追い越せないので出会うことはない
    // (2) 1周期でちょうど同じ位置にいるとき、無限回会う
    // (3) そうでないとき、いつかは出会わなくなる
    ll t1, t2; cin >> t1 >> t2;
    ll a1, a2; cin >> a1 >> a2;
    ll b1, b2; cin >> b1 >> b2;

    if (a1*t1+a2*t2==b1*t1+b2*t2) {
        // (2)の場合
        cout << "infinity" << endl;
        return;
    }

    if ((a1*t1>b1*t1 && (a1*t1)+(a2*t2)>(b1*t1)+(b2*t2)) || (a1*t1<b1*t1 && (a1*t1)+(a2*t2)<(b1*t1)+(b2*t2))) {
        // (1)の場合
        cout << 0 << endl;
        return;
    }

    // (3)の場合
    // 1周期時点での差が、その次のt1分間で追い越せなくなったら終了
    // それまでは、1周期ごとに2回ずつ出会うことになる
    ll diff;  // 1周期でできる差
    diff = abs((a1*t1+a2*t2) - (b1*t1+b2*t2));
    ll d1;
    if (b2 > a2) {
        // t1で追い越すのはa1
        d1 = (a1*t1)-(b1*t1);
    }
    else {
        d1 = (b1*t1)-(a1*t1);
    }

    ll n = d1/diff;
    ll ans = 1;
    if (d1%diff==0) {
        // 最後は追い越さず、ちょうど同じ地点になるので1回だけ出会う
        ans += (n-1)*2 + 1;
    }
    else {
        ans += n*2;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}