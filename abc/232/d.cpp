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

ll ans = 1;

void dfs(ll h, ll w, set<pair<ll,ll>>&visited, vector<string>&grid, ll &H, ll &W, ll cost) {
    ans = max(ans, cost);
    visited.insert({h,w});

    vector<pair<ll,ll>> nxt = {{h+1,w}, {h,w+1}};
    for(auto [nh, nw]: nxt) {
        if (nh<0 || nh>=H || nw<0 || nw>=W || grid[nh][nw]=='#' || visited.count({nh, nw})) continue;
        dfs(nh, nw, visited, grid, H, W, cost+1);
    }

    visited.erase({h,w});
}

void solve() {
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }

    // set<pair<ll,ll>> visited;
    // dfs(0, 0, visited, grid, H, W, 1);

    // dp
    vector<vector<ll>> dp(H, vector<ll>(W,0));
    dp[0][0] = 1;
    for(ll h=1; h<H; h++) {
        if (grid[h][0]=='.' && dp[h-1][0]!=0) {
            dp[h][0] = dp[h-1][0]+1;
        }
        else {
            dp[h][0] = 0;
        }
        ans = max(ans, dp[h][0]);
    }
    for(ll w=1; w<W; w++) {
        if (grid[0][w]=='.' && dp[0][w-1]!=0) {
            dp[0][w] = dp[0][w-1] + 1;
        }
        else {
            dp[0][w] = 0;
        }
        ans = max(ans, dp[0][w]);
    }
    for(ll h=1; h<H; h++) {
        for(ll w=1; w<W; w++) {
            if (grid[h][w]=='.' && (dp[h-1][w]!=0 || dp[h][w-1]!=0)) {
                dp[h][w] = max(dp[h-1][w], dp[h][w-1]) + 1;
            }
            else {
                dp[h][w] = 0;
            }
            ans = max(ans, dp[h][w]);
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}