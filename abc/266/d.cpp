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
    map<ll,pair<ll,ll>> sunukemp;
    ll MAX_T = 0;
    for(ll i=0; i<N; i++) {
        ll t, x, a;
        cin >> t >> x >> a;
        sunukemp[t] = {x, a};
        MAX_T = max(MAX_T, t);
    }

    // dp[t][x] := 時刻tに座標xにいるときの合計値の最大値
    vector dp(MAX_T+1, vector<ll>(5, 0));
    for(ll t=1; t<=MAX_T; t++) {
        for(ll x=0; x<=4; x++) {
            if (x-1 >= 0) dp[t][x] = max(dp[t][x], dp[t-1][x-1]);
            dp[t][x] = max(dp[t][x], dp[t-1][x]);
            if (x+1 <= 4) dp[t][x] = max(dp[t][x], dp[t-1][x+1]);
        }

        if (sunukemp.count(t)) {
            auto[sx, sa] = sunukemp[t];  // sunukeの座標と大きさ
            if (t-sx >= 0) {  // 時刻tの時点でsxに到達可能ならば
                dp[t][sx] += sa;
            }
        }
    }

    // 出力
    ll ans = 0;
    for(ll x=0; x<=4; x++) {
        ans = max(ans, dp[MAX_T][x]);
    }
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}