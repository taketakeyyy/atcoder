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


vector<ll> bfs(vector<vector<ll>> const& path, ll N, ll s) {
    vector<ll> costs(N, 0);  // 頂点sから各頂点への距離
    deque<pair<ll,ll>> deq;
    deq.push_back(make_pair(s,0));
    vector<ll> visited(N, false);
    visited[s] = true;
    while(deq.size()!=0) {
        ll u, cost;
        tie(u, cost) = deq.front(); deq.pop_front();

        for(auto v: path[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            costs[v] = cost + 1;
            deq.push_back(make_pair(v, costs[v]));
        }
    }
    return costs;
}

void solve() {
    // 最初、都市は木である
    // 木の直径を求めれば良い
    ll N; cin >> N;
    vector<vector<ll>> path(N);
    for(int i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        path[a].push_back(b);
        path[b].push_back(a);
    }

    // 木の直径は、適当な頂点からBFSをして最も遠い頂点を見つけ、その最も遠い頂点から再度BFSをすれば求まる
    vector<ll> costs;
    costs = bfs(path, N, 0);

    // 最も遠かった頂点を探す
    ll max_cost = 0;
    ll max_u = 0;
    for(int i=0; i<N; i++) {
        if (costs[i] > max_cost) {
            max_cost = costs[i];
            max_u = i;
        }
    }

    // 再度BFSをする
    costs = bfs(path, N, max_u);

    // 最も遠い頂点を探す
    max_cost = 0;
    for(int i=0; i<N; i++) {
        if (costs[i] > max_cost) {
            max_cost = costs[i];
        }
    }

    // 出力
    cout << max_cost + 1 << endl;
}


int main() {
    solve();
    return 0;
}