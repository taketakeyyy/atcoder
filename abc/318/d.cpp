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

// 最大N = 16
// 最大辺数:120
void solve() {
    ll N; cin >> N;
    vector D(N, vector<ll>(N, -1));
    vector<tuple<ll,ll,ll>> edges;
    for(ll i=0; i<N; i++) {
        for(ll j=i+1; j<N; j++) {
            ll d; cin >> d;
            D[i][j] = d;
            edges.push_back({i,j,d});
        }
    }

    ll ans = 0;
    ll E = edges.size();
    vector<bool> used(N, false); // 使った頂点
    vector<bool> memo(1<<N, false);  // メモ化
    auto dfs = [&](auto self, ll total, ll bitused) -> void {
        if (memo[bitused]) return;
        memo[bitused] = true;
        ans = max(ans, total);

        // 次の探索
        for(ll neid=0; neid<E; neid++) {
            auto[u, v, c] = edges[neid];
            if (used[u] || used[v]) continue;
            used[u] = true;
            used[v] = true;
            bitused += (1<<u) + (1<<v);
            self(self, total+c, bitused);
            used[u] = false;
            used[v] = false;
            bitused -= (1<<u) + (1<<v);
        }
    };
    dfs(dfs, 0, 0);
    cout << ans << endl;
}

void solve2() {
    ll N; cin >> N;
    vector D(N, vector<ll>(N, -1));
    vector<tuple<ll,ll,ll>> edges; // 辺(頂点u, 頂点v, 重み)のリスト
    for(ll i=0; i<N; i++) {
        for(ll j=i+1; j<N; j++) {
            ll d; cin >> d;
            D[i][j] = d;
            edges.push_back({i,j,d});
        }
    }

    ll E = edges.size();
    vector<ll> dp(1<<N, 0); // dp[bit] := 使った頂点集合がbitのときの、辺の重みの総和の最大値
    for (int bit=0; bit<(1<<N); bit++) { // 使った頂点の集合
        for(ll eid=0; eid<E; eid++) {
            auto[u, v, c] = edges[eid];
            if (bit>>u&1) continue;
            if (bit>>v&1) continue;
            ll nbit = bit + (1<<u) + (1<<v);
            dp[nbit] = max(dp[nbit], dp[bit] + c);
        }
    }

    // 答え
    ll ans = 0;
    for(ll i=0; i<1<<N; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}