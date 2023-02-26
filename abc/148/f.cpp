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

ll N;
vector<ll> bfs(ll s, vector<set<ll>> &G) {
    deque<pair<ll,ll>> deq;
    deq.push_back({s,0});
    vector<ll> visited(N, false);
    visited[s] = true;
    vector<ll> dist(N, INF);
    dist[s] = 0;
    while(!deq.empty()) {
        auto[u, cost] = deq.front(); deq.pop_front();
        for(ll v: G[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            dist[v] = cost+1;
            deq.push_back({v, cost+1});
        }
    }
    return dist;
}

// 解説AC
void solve() {
    ll u, v; cin >> N >> u >> v;
    u--; v--;
    vector<set<ll>> G(N);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].insert(b);
        G[b].insert(a);
    }

    // distT[頂点] := 高橋から各頂点の最短距離
    vector<ll> distT = bfs(u, G);
    // distA[頂点] := 青木から各頂点の最短距離
    vector<ll> distA = bfs(v, G);

    // 高橋が逃げ込める頂点のうち、青木から最も遠い頂点から答えを求める
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        if (distT[i] >= distA[i]) continue;
        ans = max(ans, distA[i]-1);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}