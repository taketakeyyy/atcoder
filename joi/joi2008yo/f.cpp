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


/// @brief ダイクストラ法で始点sからすべての頂点までの最短距離を求める
/// @param s 始点
/// @param V 頂点数
/// @param G グラフG[u] := 頂点uの有向辺(頂点v, 辺の重み)のリスト
/// @return dist[v] := 始点sから頂点vへの最短距離
vector<ll> dijkstra(ll s, ll V, vector<vector<pair<ll,ll>>> &G) {
    vector<ll> dist(V, INF); // dist[v] := 始点sから頂点vへの最短距離
    dist[s] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<>> pq;  // 小さい順を維持する優先度付きキュー
    pq.push({0,s}); // (コスト, 頂点)
    while(!pq.empty()) {
        auto[cost, u] = pq.top(); pq.pop();

        // スキップ条件
        if (dist[u] < cost) continue;

        // 探索
        for(auto [v, d]: G[u]) {
            ll ncost = cost + d; // 新しいコスト
            if (dist[v] > ncost) { // 更新処理
                dist[v] = ncost;
                pq.push({ncost, v});
            }
        }
    }
    return dist;
};

void solve() {
    ll N, K; cin >> N >> K;
    vector<vector<pair<ll,ll>>> G(N); // G[u] := 頂点uが隣接する(頂点v, コスト)のリスト
    for(ll k=0; k<K; k++) { // 高々5000回
        ll query; cin >> query;
        if (query == 0) {
            // 客の注文表
            ll a, b; cin >> a >> b;
            a--; b--;
            auto dist = dijkstra(a, N, G); // O(ElogV)。Eは徐々に増えていく。高々5000以下。O(KElogV)でも通りそう
            if (dist[b] == INF) cout << -1 << endl;
            else cout << dist[b] << endl;
        }
        else {
            // 新たな運行情報（Eが増える）
            ll c, d, e; cin >> c >> d >> e;
            c--; d--;
            G[c].push_back({d,e});
            G[d].push_back({c,e});
        }
    }
}


int main() {
    solve();
    return 0;
}