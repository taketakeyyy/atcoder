#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = tuple<long,long,set<long long>>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

vector<ll> ans;

void dfs(ll u, ll parent, set<ll>& used, vector<vector<ll>> const& paths, vector<ll> const& C) {
    bool is_me = false;  // 自分が初めて色を使う
    if (!used.count(C[u])) {
        ans.push_back(u);
        is_me = true;
    }
    used.insert(C[u]);

    for(ll v : paths[u]) {
        if (v==parent) continue;

        dfs(v, u, used, paths, C);
    }

    if (is_me) {
        used.erase(C[u]);
    }
}

void solve() {
    ll N; cin >> N;
    vector<ll> C(N);
    for(int i=0; i<N; i++) {
        cin >> C[i];
    }
    vector<vector<ll>> paths(N);
    for(int i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }

    set<ll> used;
    dfs(0, -1, used, paths, C);

    // 出力する
    sort(ans.begin(), ans.end());
    for(int i=0; i<(int)ans.size(); i++) {
        cout << ans[i]+1 << endl;
    }
}


int main() {
    solve();
    return 0;
}