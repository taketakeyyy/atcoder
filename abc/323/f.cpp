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

// 解説AC ゴールを原点に、荷物を第一象限に移動させて場合分けを減らす解法
void solve2() {
    vector<ll> X(3), Y(3);
    cin >> X[0] >> Y[0] >> X[1] >> Y[1] >> X[2] >> Y[2];

    // ゴールが原点になるように全体を平行移動させる
    X[0] -= X[2]; Y[0] -= Y[2];
    X[1] -= X[2]; Y[1] -= Y[2];
    X[2] = 0; Y[2] = 0;

    // 荷物が第一象限になるように全体を対称移動させる
    if (X[1] < 0) {
        X[1] = -X[1];
        X[0] = -X[0];
    }
    if (Y[1] < 0) {
        Y[1] = -Y[1];
        Y[0] = -Y[0];
    }

    ll ans = INF;
    {// 上から押してから、右から押す
        ll total = 0;
        if (X[0] == X[1] and Y[0] < Y[1]) {
            // 荷物の一マス上に行くには、迂回する必要がある
            total += 2;
        }
        // 荷物の一マス上に行く
        total += abs(Y[0]-(Y[1]+1)); // 荷物の一マス上のY座標に移動
        total += abs(X[0]-X[1]); // 荷物の一マス上に移動
        total += abs(Y[2]-Y[1]); // X軸に移動
        if (X[2]!=X[1]) {
            total += 2; // 右に回り込む
            total += abs(X[2]-X[1]); // 原点に移動
        }
        ans = min(ans, total);
    }
    {// 右から押してから、上から押す
        ll total = 0;
        if (Y[0]==Y[1] and X[0]<X[1]) {
            // 荷物の一マス右に行くには、迂回する必要がある
            total += 2;
        }
        // 荷物の一マス右に行く
        total += abs(X[0]-(X[1]+1));
        total += abs(Y[0]-Y[1]);
        total += abs(X[2]-X[1]);
        if (Y[2]!=Y[1]) {
            total += 2;
            total += abs(Y[2]-Y[1]);
        }
        ans = min(ans, total);
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}