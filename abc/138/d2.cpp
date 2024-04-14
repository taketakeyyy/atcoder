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

vector<vector<ll>> G;  // 木のグラフ
map<ll,ll> mp;  // mp[i] := 頂点iの部分木に足す値
vector<ll> counter;  // 各頂点のカウンター

// u:現在の頂点, parent: 親の頂点, x: 部分木に足す値
void dfs(ll u, ll parent, ll x) {
    if (mp.count(u)) x += mp[u];  // 部分木に足す値を増やす
    counter[u] += x;

    for(ll v: G[u]) {
        if (v == parent) continue;
        dfs(v, u, x);
    }

    if (mp.count(u)) x -= mp[u];  // バックトラック
}

void solve() {
    ll N, Q; cin >> N >> Q;
    G.resize(N+1);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for(ll q=0; q<Q; q++) {
        ll p, x; cin >> p >> x;
        mp[p] += x;
    }

    counter.resize(N+1, 0);
    dfs(1, -1, 0);

    // 出力
    for(ll u=1; u<=N; u++) {
        cout << counter[u] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}