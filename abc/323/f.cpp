#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

// 人と荷物の座標が与えられたときに、座標xg,ygに行くための最短歩数
ll go_to(ll xa, ll ya, ll xb, ll yb, ll xg, ll yg) {
    if (xa==xb && xa==xg && ya < yb && yb < yg) {
        return 2 + abs(xa-xg) + abs(ya-yg);
    }
    if (xa==xb && xa==xg && ya > yb && yb > yg) {
        return 2 + abs(xa-xg) + abs(ya-yg);
    }
    if (ya==yb && ya==yg && xa < xb && xb < xg) {
        return 2 + abs(xa-xg) + abs(ya-yg);
    }
    if (ya==yb && ya==yg && xa > xb && xb > xg) {
        return 2 + abs(xa-xg) + abs(ya-yg);
    }
    return abs(xa-xg) + abs(ya-yg);
}

// 荷物は最大1回曲がることで到達できる
void solve() {
    ll xa, ya, xb, yb, xc, yc; cin >> xa >> ya >> xb >> yb >> xc >> yc;
    ll ans = abs(xb-xc) + abs(yb-yc);

    if (xb == xc) {
        // 荷物と目的地のx座標が同じ
        if (yb > yc) {
            // 荷物が下なので、人は荷物の下に回り込む必要がある
            ans += go_to(xa, ya, xb, yb, xb, yb+1);
        }
        if (yc > yb) {
            // 荷物のが上なので、人は荷物の上に回り込む必要がある
            ans += go_to(xa, ya, xb, yb, xb, yb-1);
        }
    }
    else if (yb == yc) {
        // 荷物と目的地のy座標が同じ
        if (xb > xc) {
            ans += go_to(xa, ya, xb, yb, xb+1, yb);
        }
        if (xb < xc) {
            ans += go_to(xa, ya, xb, yb, xb-1, yb);
        }
    }
    else {
        if (xb > xc && yb > yc) {
            // 荷物の右側に行って、荷物の下側 or 荷物の下側に行って、荷物の右側のどちらかが最短
            ll ans1 = go_to(xa, ya, xb, yb, xb+1, yb) + 2;
            ll ans2 = go_to(xa, ya, xb, yb, xb, yb+1) + 2;
            ans += min(ans1, ans2);
        }
        if (xb > xc && yb < yc) {
            // 荷物の右側、荷物の上側
            ll ans1 = go_to(xa, ya, xb, yb, xb+1, yb) + 2;
            ll ans2 = go_to(xa, ya, xb, yb, xb, yb-1) + 2;
            ans += min(ans1, ans2);
        }
        if (xb < xc && yb > yc) {
            // 荷物の左側、荷物の下側
            ll ans1 = go_to(xa, ya, xb, yb, xb-1, yb) + 2;
            ll ans2 = go_to(xa, ya, xb, yb, xb, yb+1) + 2;
            ans += min(ans1, ans2);
        }
        if (xb < xc && yb < yc) {
            // 荷物の左側、荷物の上側
            ll ans1 = go_to(xa, ya, xb, yb, xb-1, yb) + 2;
            ll ans2 = go_to(xa, ya, xb, yb, xb, yb-1) + 2;
            ans += min(ans1, ans2);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}