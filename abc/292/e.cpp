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

ll N, M;
vector<vector<ll>> G; // G[u][v] := uからvへの有向辺
vector<vector<bool>> H; // 追加した辺も含む、最終的なグラフH
ll ans = 0;
void dfs(ll u, vector<bool> &visited, ll start, vector<bool> &memo) {
    // 終了条件
    if (memo[u]) return; // 探索済みノードは即時リターン
    memo[u] = true;

    // 探索
    for(ll v: G[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        if (start != u && u != v && v != start) {
            if (!H[start][v]) {
                H[start][v] = true;
                ans++;
            }
        }
        dfs(v, visited, start, memo);
        visited[v] = false;
    }
}

void solve() {
    cin >> N >> M;
    G.resize(N);
    H.resize(N);
    for(ll i=0; i<N; i++) H[i].resize(N,false);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        H[u][v] = true;
    }

    for(ll u=0; u<N; u++) {
        vector<bool> visited(N, false);
        vector<bool> memo(N, false);  // メモ化再帰しないとTLEは典型
        visited[u] = true;
        dfs(u, visited, u, memo);
    }

    // 出力
    cout << ans << endl;
}

// 解説解法
// ワーシャルフロイド解法 O(N^3) 定数倍が軽い
// bitsetを使うことで1/64にできるらしい
void solve2() {
    cin >> N >> M;
    vector<bitset<2000>> g(N); // g[i][j] := iからjへ辺がある
    for(ll i=0; i<N; i++) g[i][i] = 1;
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        g[u][v] = 1;
    }

    // ワーシャルフロイド
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            // for(j=0; j<N; j++) g[i][j] |= g[i][k]&g[k][j];
            // 「iからkへ行ける」ならば「iから到達可能な頂点」に「kから到達可能な頂点」をすべて足す
            if (g[i][k]) g[i] |= g[k];
        }
    }

    // 答え
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ans += g[i].count();
    }
    ans -= M+N;
    cout << ans << endl;
}

// 解説AC
// すべての頂点からBFS O(N(N+M))
void solve3() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> to(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        to[u].push_back(v);
    }

    ll ans = 0;
    for(ll s=0; s<N; s++) {
        vector<bool> can(N); // 到達可能か
        can[s] = true;
        queue<ll> que;
        que.push(s);
        while(que.size()) {
            ll u = que.front(); que.pop();
            for(ll v: to[u]) {
                if (can[v]) continue;
                can[v] = true;
                que.push(v);
                ans++;
            }
        }
    }
    ans -= M;
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    // solve3();
    return 0;
}