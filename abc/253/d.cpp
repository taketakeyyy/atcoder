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


ll f(ll x, ll MAX) {
    // 1から10^9までの、xの倍数の和を求める
    ll a = x;
    ll n = MAX/x;
    ll l = n*x;
    return n*(a+l)/2;
}

void solve() {
    ll N, A, B; cin >> N >> A >> B;
    ll ans = f(1, N) - f(A, N) - f(B, N) + f(lcm(A, B), N);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}