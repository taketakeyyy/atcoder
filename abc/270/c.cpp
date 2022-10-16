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

ll N, X, Y;
vector<set<ll>> tree;
vector<ll> ans;
void dfs(ll now, set<ll> &visited) {
    if (now == Y) {
        // 出力
        for(ll i=0; i<ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        exit(0);
    }

    for(auto v: tree[now]) {
        if (visited.count(v)) continue;
        visited.insert(v);
        ans.push_back(v);
        dfs(v, visited);
        visited.erase(v);
        ans.pop_back();
    }
}

void solve() {
    cin >> N >> X >> Y;
    tree.resize(N+1);
    for(ll i=1; i<=N-1; i++) {
        ll u, v; cin >> u >> v;
        tree[u].insert(v);
        tree[v].insert(u);
    }

    ans.push_back(X);
    set<ll> visited; visited.insert(X);
    dfs(X, visited);

}


int main() {
    solve();
    return 0;
}