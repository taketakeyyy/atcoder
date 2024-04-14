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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, S, M, L; cin >> N >> S >> M >> L;
    vector<ll> dp(N+12+1, INF);
    dp[0] = 0;
    for(ll i=1; i<=N+12; i++) {
        auto newdp = dp;
        if (i-6>=0 && dp[i-6]!=INF) {
            chmin(newdp[i], dp[i-6]+S);
        }
        if (i-8>=0 && dp[i-8]!=INF) {
            chmin(newdp[i], dp[i-8]+M);
        }
        if (i-12>=0 && dp[i-12]!=INF) {
            chmin(newdp[i], dp[i-12]+L);
        }
        swap(dp, newdp);
    }

    ll ans = INF;
    for(ll i=N; i<=N+12; i++) chmin(ans, dp[i]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}