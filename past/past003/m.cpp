#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


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
    ll N, M; cin >> N >> M;
    vector<vector<pair<ll,ll>>> G(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back({v,1});
        G[v].push_back({u,1});
    }
    ll S; cin >> S; S--;
    ll K; cin >> K;
    vector<ll> T(K);
    for(ll k=0; k<K; k++) {
        cin >> T[k]; T[k]--;
    }

    // K+1回ダイクストラする
    auto distS = dijkstra(S, N, G);
    map<ll,vector<ll>> dist;
    for(ll k=0; k<K; k++) {
        dist[T[k]] = dijkstra(T[k], N, G);
    }

    // 通る街をbitDP
    // (1) dpの宣言
    // dp[S][i] := 現在位置が都市iで、今まで訪れた都市集合がSのときの最小コスト
    vector<vector<ll>> dp(1<<K, vector<ll>(K, INF));

    // (2) dpの初期化
    // 都市Sからスタートなので、都市Sから都市iへのコストは計算しておくと便利（都市Sは訪問したこと無い扱い）
    for(ll i=0; i<K; i++) {
        dp[1<<i][i] = distS[T[i]];
    }

    // (3) dpを埋めていく
    for (ll bit=0; bit<(1<<K); bit++) {
        for (ll i=0; i<K; i++) { // 現在の都市i
            if (~bit>>i&1) continue; // iはまだ訪れていない
            for (ll j=0; j<K; j++) {  // 次に行く都市j
                if (bit>>j&1) continue; // jはすでに訪れている
                // iが訪問済みで、jはまだ訪れていないなら、
                dp[bit|1<<j][j] = min(dp[bit|1<<j][j], dp[bit][i]+dist[T[i]][T[j]]);
            }
        }
    }

    // 答え
    ll ans = INF;
    for(ll k=0; k<K; k++) chmin(ans, dp[(1<<K)-1][k]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}