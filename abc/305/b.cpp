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
    vector<ll> A = {3,1,4,1,5,9};
    vector<ll> ruiseki(7,0);
    for(ll i=1; i<=6; i++) {
        ruiseki[i] = ruiseki[i-1] + A[i-1];
    }
    char p, q; cin >> p >> q;
    ll i = min(p-'A', q-'A');
    ll j = max(p-'A', q-'A');
    ll ans = abs(ruiseki[i] - ruiseki[j]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}