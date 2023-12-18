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


void solve() {
    ll N; cin >> N;
    vector<vector<ll>> G(N);
    vector<ll> deg(N); // 次数
    for(ll i=0; i<N-1; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    auto dfs = [&](auto dfs, ll u, vector<bool> &visited) -> ll {
        // 終了条件

        // 次の探索
        ll cost = 0;
        for(ll v: G[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            cost += dfs(dfs, v, visited);
            visited[v] = false;
        }

        return cost+1;
    };

    if (deg[0] == 1) {
        cout << 1 << endl;
    }
    else {
        vector<ll> ress;
        for(ll v: G[0]) {
            vector<bool> visited(N, false);
            visited[0] = true;
            visited[v] = true;
            ll cost = dfs(dfs, v, visited);
            ress.push_back(cost);
        }
        sort(ress.begin(), ress.end());
        ll ans = accumulate(ress.begin(), ress.end(), 0LL);
        ans -= ress.back();
        cout << ans+1 << endl;
    }
}


int main() {
    solve();
    return 0;
}