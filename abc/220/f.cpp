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
    for(ll i=0; i<N-1; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<ll> size(N); // size[u] := 頂点0から下っていったときの、頂点uを根としたときの部分木のサイズ
    {// 各sizeを求める
        auto dfs = [&](auto dfs, ll u, ll parent) -> ll {
            // 次の探索
            ll res = 1;
            for(ll v: G[u]) {
                if (v == parent) continue;
                res += dfs(dfs, v, u);
            }
            return size[u] = res;
        };
        dfs(dfs, 0, -1);
    }

    vector<ll> ans(N);
    {// 頂点0の答えをまず求める
        auto dfs = [&](auto dfs, ll u, ll parent, ll depth) -> ll {
            // 次の探索
            ll res = 0;
            for(ll v: G[u]) {
                if (v == parent) continue;
                res += dfs(dfs, v, u, depth+1);
            }
            return res + depth;
        };
        ans[0] = dfs(dfs, 0, -1, 0);
    }
    {//その他の頂点についても求める
        auto dfs = [&](auto dfs, ll u, ll parent) -> void {
            if (u != 0LL) {
                ans[u] = ans[parent] - size[u] + (N-size[u]);
            }

            // 次の探索
            for(ll v: G[u]) {
                if (v == parent) continue;
                dfs(dfs, v, u);
            }
        };
        dfs(dfs, 0, -1);
    }

    // 答え
    for(ll u=0; u<N; u++) {
        cout << ans[u] << endl;
    }
}


int main() {
    solve();
    return 0;
}