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


void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].insert(b);
        G[b].insert(a);
    }

    // dp[k] := 頂点kに到達するときの最短距離の場合の数
    vector<ll> dp(N, 0);
    dp[0] = 1;
    vector<ll> dist(N, INF);  // 最短距離
    dist[0] = 0;
    // BFSで解くO(頂点数＋辺数)
    deque<pair<ll,ll>> que;  // {頂点番号, コスト}
    que.push_back({0, -1});
    set<ll> visited;
    visited.insert(0);

    while(!que.empty()) {
        ll u, c;
        tie(u, c) = que.front();
        que.pop_front();

        if (u == N-1) {
            break;
        }

        // キューと最短距離の更新
        for(ll v: G[u]) {
            if (visited.count(v)) continue;
            visited.insert(v);
            dist[v] = c+1;
            que.push_back({v, dist[v]});
        }

        // 場合の数更新
        for(ll v: G[u]) {
            if (dist[v] == c+1) {
                dp[v] += dp[u];
                dp[v] %= MOD;
            }
        }
    }

    // 出力
    cout << dp[N-1] << endl;
}


int main() {
    solve();
    return 0;
}