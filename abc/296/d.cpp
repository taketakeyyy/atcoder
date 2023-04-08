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


// 解説AC
void solve() {
    ll N, M; cin >> N >> M;
    ll ans = INF;

    for(ll a=1; a<=sqrt(M)+1; a++) {
        if (a > N) break;
        ll b = (M+(a-1))/a; // 切り上げ
        if (!(1<=b && b<=N)) continue;
        ll X = a*b;
        ans = min(ans, X);
    }

    cout << ((ans==INF)? -1 : ans) << endl;
}

void solve2() {
    ll N, M; cin >> N >> M;

    // a<=b という制約をつけて、a=1から試していく
    ll ans = INF;
    for(ll a=1; a<=INF; a++) {
        ll b = (M+(a-1))/a; // 切り上げ
        if (a > b) break;
        if (!(1<=b && b<=N)) continue;
        ll X = a*b;
        if (X >= M) ans = min(ans, X);
    }
    cout << ((ans==INF) ? -1 : ans) << endl;
}



int main() {
    // solve();
    solve2();
    return 0;
}