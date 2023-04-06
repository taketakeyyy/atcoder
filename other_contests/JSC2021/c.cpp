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


void solve() {
    ll A, B; cin >> A >> B;

    auto f = [&](ll z) {
        ll x = intceil(A,z)*z;
        ll y = x + z;
        return (A<=x && x<=B && y<=B);
    };

    ll l = 1, r = 2e5;
    while(r-l != 1) {
        ll mid = (r+l)/2;
        if (f(mid)) l = mid;
        else r = mid;
    }
    if (f(r)) cout << r << endl;
    else cout << l << endl;
}

void solve2() {
    ll A, B; cin >> A >> B;

    // gcd(x,y)がdのとき、xとyは条件を満たすか？
    auto f = [&](ll d) {
        ll x = intceil(A,d)*d;
        ll y = x + d;
        return (A<=x && x<=B && y<=B);
    };

    // dを全部試す
    ll ans = 1;
    for(ll d=1; d<=B; d++) {
        if (f(d)) ans = d;
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}