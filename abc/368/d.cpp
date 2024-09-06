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
    ll N, K; cin >> N >> K;
    vector<vector<ll>> G(N);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    vector<ll> V(K);
    set<ll> Vset;
    for(ll i=0; i<K; i++) {
        cin >> V[i];
        V[i]--;
        Vset.insert(V[i]);
    }

    unordered_set<ll> rest; // 残す頂点
    auto dfs = [&](auto dfs, ll u, ll parent) -> bool {
        bool res = false; // この頂点uを残すか？

        for(ll v: G[u]) {
            if (v == parent) continue;
            res |= dfs(dfs, v, u);
        }

        if (Vset.count(u)) res = true;
        if (res) rest.insert(u);
        return res;
    };
    dfs(dfs, V[0], -1);

    // 答え
    cout << rest.size() << endl;
}


int main() {
    solve();
    return 0;
}