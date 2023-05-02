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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll A, B, C, D; cin >> A >> B >> C >> D;
    if (C*D-B <= 0) {
        cout << -1 << endl;
        return;
    }

    auto f = [&](ll x) {
        return (A <= x*(C*D-B));
    };

    ll l=1, r=1e8;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) cout << l << endl;
    else cout << r << endl;
}

void solve2() {
    ll A, B, C, D; cin >> A >> B >> C >> D;
    if (C*D-B <= 0) {
        cout << -1 << endl;
        return;
    }

    ll n = intceil(A, C*D-B);
    cout << n << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}