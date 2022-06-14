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

vector<set<ll>> G;  // グラフ

void dfs(ll now, ll depth, set<ll> &visited, set<ll> &counted, ll &ans) {
    if (depth == 0) { return; }

    for(ll v: G[now]) {
        if (visited.count(v)) continue;
        if (!counted.count(v)) {
            ans += v;
        }
        visited.insert(v);
        counted.insert(v);
        dfs(v, depth-1, visited, counted, ans);
        visited.erase(v);
    }
}

void solve() {
    ll N, M; cin >> N >> M;
    G.resize(N+1);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        G[a].insert(b);
        G[b].insert(a);
    }

    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {  // O(Q)
        ll x, k; cin >> x >> k;
        set<ll> visited; visited.insert(x);  // 訪れた頂点番号
        set<ll> counted; counted.insert(x);  // 数え終わった頂点番号
        ll ans = x;
        dfs(x, k, visited, counted, ans);  // O(3^k)  // 各頂点の次数はたかだか3なので
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}