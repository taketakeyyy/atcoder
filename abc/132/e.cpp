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


// TLE
void solve_TLE() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v);
    }
    ll S, T; cin >> S >> T; S--; T--;

    // けんけんぱ一回分（3回移動）用のグラフG3を構築する
    // O(M^3) TLE
    vector<vector<ll>> G3(N);
    for(ll i=0; i<N; i++) {
        for(ll v1: G[i]) {
            for(ll v2: G[v1]) {
                for(ll v3: G[v2]) {
                    G3[i].push_back(v3);
                }
            }
        }
    }

    // BFS  O(N + M)
    vector<ll> dist(N, -1);  // dist[i] := 頂点iへの最短距離（最小けんけんぱ回数）
    dist[S] = 0;
    deque<pair<ll,ll>> deq;  // {コスト, 頂点番号}
    deq.push_back({0, S});
    while(!deq.empty()) {
        auto[cost, u] = deq.front(); deq.pop_front();

        if (u == T) { break; }

        for(auto v: G3[u]) {
            if (dist[v] != -1) { continue; }
            dist[v] = cost + 1;
            deq.push_back({cost+1, v});
        }
    }

    cout << dist[T] << endl;
}


// AC
void solve() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v; u--; v--;
        G[u].push_back(v);
    }
    ll S, T; cin >> S >> T; S--; T--;

    // 拡張BFS
    // dist[i][j] := 頂点iへの最短移動回数。j=移動回数%3
    vector dist(N, vector<ll>(3, -1));
    dist[S][0] = 0;
    deque<pair<ll,ll>> deq;  // {累積移動回数, 頂点番号}
    deq.push_back({0,S});
    while(!deq.empty()) {
        auto[cost, u] = deq.front(); deq.pop_front();

        if (u==T && dist[u][0] != -1) { break; }

        for(ll v: G[u]) {
            if (dist[v][(cost+1)%3] != -1) { continue; }
            dist[v][(cost+1)%3] = cost+1;
            deq.push_back({cost+1, v});
        }
    }
    // 出力
    cout << ((dist[T][0]==-1)? -1 : dist[T][0]/3) << endl;
}

int main() {
    solve();
    return 0;
}