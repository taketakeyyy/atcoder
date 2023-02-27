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
    ll N; cin >> N;
    vector<ll> X;
    for(ll i=0; i<5*N; i++) {
        ll x; cin >> x;
        X.push_back(x);
    }
    sort(X.begin(), X.end());

    double total = 0.;
    for(ll i=N; i<=4*N-1; i++) {
        total += X[i];
    }
    double ans = total/(3*N);
    printf("%.8lf\n", ans);

}


int main() {
    solve();
    return 0;
}