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

bool is_cycle_dfs(ll now, ll parent, set<ll> &visited, const vector<vector<ll>> &graph) {
    visited.insert(now);

    for(ll v: graph[now]) {
        if (v == parent) continue;
        if (visited.count(v)) return true;
        bool res = is_cycle_dfs(v, now, visited, graph);
        if (res) return true;
    }
    return false;
}

void solve() {
    ll N, M; cin >> N >> M;
    // すべての頂点の次数が2以下か？
    vector<ll> jisu(N);  // 次数
    // サイクルができたら駄目
    vector<vector<ll>> graph(N);  // 無向辺グラフ
    bool is_2 = true;  // 次数が2以下？
    for(ll m=0; m<M; m++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        jisu[a]++;
        jisu[b]++;
        graph[a].push_back(b);
        graph[b].push_back(a);

        if (jisu[a] > 2 || jisu[b] > 2) {
            is_2 = false;
            break;
        }
    }

    // サイクル検出
    bool is_cycle = false;  // サイクルあるか？
    set<ll> visited;
    for(ll i=0; i<N; i++) {
        if (visited.count(i)) continue;

        bool res = is_cycle_dfs(i, -1, visited, graph);
        if (res) {
            is_cycle = true;
            break;
        }
    }

    if (is_2 && !is_cycle) {
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