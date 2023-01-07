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

vector<ll> memo;
vector<set<ll>> G;
ll K = 0;

void dfs(ll u, vector<bool> &visited) {
    memo[u]++;
    K++;
    if (K >= 1000000) {  // これ忘れないように！
        cout << 1000000 << endl;
        exit(0);
    }

    for(ll v: G[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        dfs(v, visited);
        visited[v] = false;
    }
}

void solve() {
    ll N, M; cin >> N >> M;
    memo.resize(N, 0);
    G.resize(N);

    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].insert(v);
        G[v].insert(u);
    }

    vector<bool> visited(N, false);
    visited[0] = true;
    dfs(0, visited);

    // 答え
    ll ans = 0;
    for(ll u=0; u<N; u++) {
        ans += memo[u];
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}