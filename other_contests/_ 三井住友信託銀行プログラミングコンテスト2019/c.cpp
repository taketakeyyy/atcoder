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
    ll X; cin >> X;

    // dp[x] := x円を作れるかどうか
    vector<bool> dp(X+1, false);
    dp[0] = true;
    for(ll i=0; i<(X/100)+1; i++) {
        for(ll x=0; x<=X; x++) {
            if (x-100>=0 && dp[x-100]) dp[x] = true;
            if (x-101>=0 && dp[x-101]) dp[x] = true;
            if (x-102>=0 && dp[x-102]) dp[x] = true;
            if (x-103>=0 && dp[x-103]) dp[x] = true;
            if (x-104>=0 && dp[x-104]) dp[x] = true;
            if (x-105>=0 && dp[x-105]) dp[x] = true;
        }
    }
    if (dp[X]) cout << 1 << endl;
    else cout << 0 << endl;
}


int main() {
    solve();
    return 0;
}