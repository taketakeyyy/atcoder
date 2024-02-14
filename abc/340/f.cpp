#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
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


// 拡張ユークリッドの互除法
// ax + by = gcd(a,b)を満たす整数解x,yを求める
//
// Args:
//     a(int)
//     b(int)
//
// Returns:
//     d, x, y(tuple)
//         d(int): gcd(a,b)
//         x(int): xの整数解
//         y(int): yの整数解
tuple<ll,ll,ll> extgcd(ll a, ll b) {
    auto _extgcd = [](auto _extgcd, ll a, ll b, ll x, ll y) -> tuple<ll,ll,ll> {
        if (b==0) return {a,1,0};
        ll p = a/b;
        auto[g, yy, xx] = _extgcd(_extgcd, b, a-b*p, y, x);
        yy -= p*xx;
        return {g,xx,yy};
    };
    return _extgcd(_extgcd,a,b,0,0);
}


//解説AC　拡張ユークリッドの互除法
void solve() {
    ll x1, y1; cin >> x1 >> y1;
    // x1y2 + y1x2 = g の整数解(x2,y2)を求める
    auto[g, y2, x2] = extgcd(x1, y1);

    // x1y2 - y1x2 = g の整数解が知りたいので、x2の符号を入れ替える
    x2 = -x2;

    // gは1か2のはず。
    if (abs(g) > 2) {
        cout << -1 << endl;
        return;
    }

    // x1y2 - y1x2 = 2 になるように調整
    y2 *= 2/g; x2 *= 2/g;
    cout << x2 << " " << y2 << endl;
}

//解説AC　拡張ユークリッドの互除法
void solve2() {
    ll x1, y1; cin >> x1 >> y1;
    // x1y2 + y1x2 = g の整数解(x2,y2)を求める
    auto[g, y2, x2] = extgcd(x1, y1);

    // x1y2 - y1x2 = g の整数解が知りたいので、x2の符号を入れ替える
    x2 = -x2;

    // 答え
    if (abs(g)==2) {
        cout << x2 << " " << y2 << endl;
        return;
    }
    else {
        if (x2%g==0 and y2%g==0) {
            x2 *= 2/g;
            y2 *= 2/g;
            cout << x2 << " " << y2 << endl;
            return;
        }
        else {
            cout << -1 << endl;
            return;
        }
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}