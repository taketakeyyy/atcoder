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
vector<set<ll>> G;
vector<ll> ans;

void dfs(ll u, ll pre, set<ll> &visited) {
    cout << u+1 << " ";

    for(ll v: G[u]) {
        if (v == pre) continue;
        if (visited.count(v)) continue;

        visited.insert(v);
        dfs(v, u, visited);
        visited.erase(v);
        cout << u+1 << " ";
    }
}

void solve() {
    cin >> N;
    G.resize(N);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].insert(b);
        G[b].insert(a);
    }

    // priority_queue<ll, vector<ll>, greater<ll>> pq;
    // pq.push(0);
    set<ll> visited;
    dfs(0, -1, visited);
}


int main() {
    solve();
    return 0;
}