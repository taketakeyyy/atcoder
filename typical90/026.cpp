#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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

void dfs(ll u, bool is_pick, vector<vector<ll>> &tree, ll const N, set<ll> &ans, set<ll> &visited) {
    if ((ll)ans.size()==N/2) return;
    if (visited.count(u)) return;

    visited.insert(u);
    if (is_pick) {
        ans.insert(u);
    }

    for(auto v: tree[u]) {
        dfs(v, !is_pick, tree, N, ans, visited);
    }
}

void solve() {
    ll N; cin >> N;

    // 木構造を作って、頂点0(根)から1個飛ばしに頂点を取り出せば良い。
    // 根を取るパターンと、根を取らないパターンの2パターンを走査して、N/2頂点取り出せる方を探す
    vector<vector<ll>> tree(N);
    for(int i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // 根から取るパターン
    set<ll> ans;
    set<ll> visited;
    dfs(0, true, tree, N, ans, visited);
    if ((ll)ans.size()==N/2) {
        for(auto u: ans) {
            cout << u+1 << " ";
        }
        cout << endl;
        return;
    }

    // 根を取らないパターン
    ans = set<ll>();
    visited = set<ll>();
    dfs(0, false, tree, N, ans, visited);
    if ((ll)ans.size()==N/2) {
        for(auto u: ans) {
            cout << u+1 << " ";
        }
        cout << endl;
        return;
    }
}


int main() {
    solve();
    return 0;
}