#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


vector<ll> dijkstra(ll s, ll N, map<pair<ll,ll>, ll> &costs, vector<vector<ll>> const &graph) {
    vector<ll> dists(N, INF);
    dists[s] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> que;
    que.push(make_pair(0, s));

    while(!que.empty()) {
        ll u, d;
        tie(d, u) = que.top(); que.pop();

        if (dists[u] < d) continue;

        for (ll i=0; i<(ll)graph[u].size(); i++) {
            ll v = graph[u][i];
            ll cost = costs[make_pair(min(u,v),max(u,v))];

            if (dists[v] > dists[u]+cost) {
                dists[v] = dists[u]+cost;  // 更新
                que.push(make_pair(dists[v], v));
            }
        }
    }

    return dists;
}

void solve() {
    ll N, M; cin >> N >> M;
    map<pair<ll,ll>, ll> costs;
    vector<vector<ll>> graph(N, vector<ll>(0));
    for (int i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        costs[make_pair(min(a,b), max(a,b))] = c;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 各頂点でダイクストラしてたら間に合わない
    // 「1からiまでの最短距離」+「iからNまでの最短距離」をすればいいので、
    // 「1から各頂点」、「Nから各頂点」のダイクストラを2回すればOK
    vector<ll> dists0 = dijkstra(0, N, costs, graph);
    vector<ll> distsN = dijkstra(N-1, N, costs, graph);

    // 出力
    for(int i=0; i<N; i++) {
        cout << dists0[i]+distsN[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}