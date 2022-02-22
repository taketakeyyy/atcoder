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

ll N;
vector<set<ll>> tree;
ll g_id = 1;
vector<pair<ll,ll>> ans;

pair<ll,ll> dfs(ll now, ll parent) {
    ll mn=INF, mx=-INF;
    for(ll v: tree[now]) {
        if (v == parent) continue;
        pair<ll,ll> res = dfs(v, now);
        mn = min(mn, res.first);
        mx = max(mx, res.second);
    }

    if (mn == INF) {
        // 葉の処理
        mn = g_id;
        mx = g_id;
        g_id++;
    }

    ans[now] = {mn, mx};
    return {mn, mx};
}

void solve() {
    cin >> N;
    tree.resize(N);
    ans.resize(N);
    for(ll i=0; i<N-1; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        tree[u].insert(v);
        tree[v].insert(u);
    }

    dfs(0, -1);

    for(ll i=0; i<N; i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}


int main() {
    solve();
    return 0;
}