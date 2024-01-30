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


vector<int> BFS(int n, vector<vector<int>>& paths, int& N) {
    // BFSで宝石nから各宝石までの距離を求める
    vector<int> dist(N, INT_MAX); dist[n] = 0;
    set<int> visited; visited.insert(n);
    deque<int> que; que.push_back(n);
    while(!que.empty()) {
        int now = que.front();
        que.pop_front();

        for (int nx: paths[now]) {
            if (visited.count(nx)) continue;
            visited.insert(nx);
            dist[nx] = min(dist[nx], dist[now]+1);
            que.push_back(nx);
        }
    }
    return dist;
}

// AC
void solve2(){
    int N, M; cin >> N >> M;
    vector<vector<int>> paths(N);
    for (int i=0; i<M; i++) {
        int A, B; cin >> A >> B; A--; B--;
        paths[A].push_back(B);
        paths[B].push_back(A);
    }

    int K; cin >> K;
    vector<int> Cs(K);
    for (int i=0; i<K; i++) {
        int C; cin >> C; C--;
        Cs[i] = C;
    }

    vector<vector<int>> dists;
    for (int i=0; i<K; i++) {
        dists.emplace_back(BFS(Cs[i], paths, N));  // 始点cからの最短距離を求める
    }

    // bitDP[S][i] := 既に訪れた重要宝石集合Sにおいて、現在の重要宝石がiのときの、最短距離
    vector<vector<int>> dp(1<<K, vector<int>(K, INT_MAX));
    for (int i=0; i<K; i++) {
        dp[0][i] = 0;
    }
    for (int i=0; i<K; i++) {
        for (int j=0; j<K; j++) {
            dp[(1<<i)|(1<<j)][j] = dists[i][Cs[j]];
        }
    }
    for (int S=1; S<(1<<K); S++) {
        for (int i=0; i<K; i++) {  // 現在の宝石i
            if (~S>>i&1) continue;  // iはまだ訪れていない
            for (int j=0; j<K; j++) {  // 次に行く宝石j
                if (S>>j&1) continue;  // jは既に訪れている
                int new_cost = dp[S][i]+dists[i][Cs[j]];
                if (new_cost<0) new_cost = INT_MAX;  // オーバーフロー対策
                dp[S|1<<j][j] = min(dp[S|1<<j][j], new_cost);
            }
        }
    }

    // 答え
    int ans = INT_MAX;
    for (int i=0; i<K; i++) {
        ans = min(ans, dp[pow(2,K)-1][i]);
    }
    if (ans == INT_MAX) {
        cout << -1 << endl;
    }
    else {
        cout << ans+1 << endl;
    }
}

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

// AC
void solve3(){
    ll N, M; cin >> N >> M;
    vector<vector<pair<ll,ll>>> G(N); // G[u] := 宝石uと隣り合っても良い宝石のリスト
    for (ll i=0; i<M; i++) {
        ll A, B; cin >> A >> B; A--; B--;
        G[A].push_back({B,1});
        G[B].push_back({A,1});
    }
    ll K; cin >> K;
    vector<ll> C(K);
    for (ll i=0; i<K; i++) {
        cin >> C[i]; C[i]--;
    }

    // dist[u][v] := 宝石uから宝石vへの最短距離（使う宝石の最小個数）
    map<ll,vector<ll>> dist;
    for(ll i=0; i<K; i++) {
        ll c = C[i];
        dist[c] = dijkstra(c, N, G);
    }

    // dp[i][S] := 現在いる重要宝石がiで、今まで訪れた重要宝石の集合がSのときの、使う宝石の最小個数
    vector dp(K, vector(1<<K, INF));
    // dp初期化
    for(ll i=0; i<K; i++) {
        dp[i][1<<i] = 1; // 重要宝石iからスタートするとき、重要宝石は1個使う
    }
    // bitDP
    for(ll bit=0; bit<(1<<K); bit++) {
        for(ll i=0; i<K; i++) { // 現在の重要宝石
            if (dp[i][bit]==INF) continue;
            if (~bit>>i&1) continue; // まだ訪れていないならスキップ
            for(ll j=0; j<K; j++) { // 次に訪問する重要宝石
                if (bit>>j&1) continue; // すでに訪れているならスキップ
                if (dist[C[i]][C[j]]==INF) continue;
                chmin(dp[j][bit|(1LL<<j)], dp[i][bit]+dist[C[i]][C[j]]);
            }
        }
    }

    // 答え
    ll ans = INF;
    for(ll i=0; i<K; i++) {
        chmin(ans, dp[i][(1<<K)-1]);
    }
    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;
}


int main(){
    // solve2();
    solve3();
    return 0;
}