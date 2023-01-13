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


// ・円が完全に長方形を内包しているか
//   - これは長方形の4つの頂点が円の中に入っているか確認すればよい
//   - 長方形の各頂点と円の中心からの距離がr以内になっているか？
// ・長方形が完全に円を内包しているか
// を調べれば良い
void solve() {
    ll x1, y1, r; cin >> x1 >> y1 >> r;
    ll x2, y2, x3, y3; cin >> x2 >> y2 >> x3 >> y3;

    // 円が完全に長方形を内包しているか
    auto is_in_circle = [&x1, &y1, &r](ll x, ll y) {
        return (x1-x)*(x1-x) + (y1-y)*(y1-y) <= r*r;
    };
    if (is_in_circle(x2,y2) && is_in_circle(x3,y3) && is_in_circle(x2,y3) && is_in_circle(x3,y2)) {
        cout << "YES" << endl;
        cout << "NO" << endl;
        return;
    }
    // 長方形が完全に円を内包しているか
    if (x2<=x1-r && x1+r<=x3 && y1-r>=y2 && y1+r<=y3) {
        cout << "NO" << endl;
        cout << "YES" << endl;
        return;
    }
    cout << "YES" << endl;
    cout << "YES" << endl;
}


int main() {
    solve();
    return 0;
}