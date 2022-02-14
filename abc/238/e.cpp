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


bool dfs(ll now, set<ll> &visited, vector<set<ll>> &graph, ll N) {
    if (now == N) {
        return true;
    }
    visited.insert(now);

    for (auto v: graph[now]) {
        if (visited.count(v)) continue;
        bool res = dfs(v, visited, graph, N);
        if (res) return true;
    }

    visited.erase(now);
    return false;
}

bool bfs(vector<set<ll>> &graph, ll N) {
    deque<ll> que;
    que.push_back(0);
    set<ll> visited; visited.insert(0);

    while(!que.empty()) {
        ll u = que.front(); que.pop_front();
        if (u == N) { return true; }

        for(auto v: graph[u]) {
            if (visited.count(v)) continue;
            visited.insert(v);
            que.push_back(v);
        }
    }
    return false;
}

void solve() {
    ll N, Q; cin >> N >> Q;
    vector<set<ll>> graph(N+1);
    for (ll q=0; q<Q; q++) {
        ll l, r; cin >> l >> r;
        l--;
        graph[l].insert(r);
        graph[r].insert(l);
    }

    // graph[0] から graph[N]に到達可能か？
    // set<ll> visited;
    // bool ans = dfs(0, visited, graph, N);
    bool ans = bfs(graph, N);

    if (ans) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}