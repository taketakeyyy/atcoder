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



ll N, Q;
vector<ll> X;
vector<set<ll>> tree;
vector<vector<ll>> pqtree;

void dfs2(ll now, ll parent) {
    for (ll v: tree[now]) {
        if (v == parent) continue;
        dfs2(v, now);
        pqtree[now].insert(pqtree[now].end(), pqtree[v].begin(), pqtree[v].end());
    }

    pqtree[now].push_back(X[now]);
    sort(pqtree[now].begin(), pqtree[now].end());
    reverse(pqtree[now].begin(), pqtree[now].end());
    if (pqtree[now].size() > 20) {
        pqtree[now].resize(20);
    }
}


void solve() {
    // Kの制約が小さいことに注目！！！
    cin >> N >> Q;
    X.resize(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i];
    }
    tree.resize(N);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        tree[a].insert(b);
        tree[b].insert(a);
    }

    pqtree.resize(N);
    dfs2(0, -1);

    // クエリ
    for (ll q=0; q<Q; q++) {
        ll v, k; cin >> v >> k;
        v--;
        k--;
        cout << pqtree[v][k] << endl;
    }
}


int main() {
    solve();
    return 0;
}