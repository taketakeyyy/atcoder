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
    double ans = 0.;
    for(ll i=0; i<N; i++) {
        double now = 0.;
        for(ll j=1; j<=6; j++) {
            now += max(double(j), ans);
        }
        ans = now/6;
    }

    printf("%.10lf\n", ans);
}

// 「スコアの期待値が最大になるように行動する」 = 「期待値より小さい目が出たら、再度振る」
// dp[i] := i回振れるときの期待値
void solve2() {
    ll N; cin >> N;
    vector<double> dp(N+1, 0);
    dp[1] = (double)(1+2+3+4+5+6)/6.0;
    for(ll i=2; i<=N; i++) {
        for(ll j=1; j<=6; j++) {  // 出目
            if (j >= dp[i-1]) dp[i] += j;
            else dp[i] += dp[i-1];
        }
        dp[i] /= 6.0;
    }
    printf("%.16lf\n", dp[N]);
}


int main() {
    // solve();
    solve2();
    return 0;
}