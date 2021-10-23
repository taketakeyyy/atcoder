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

vector<vector<ll>> G;
vector<ll> node_num;

void dfs(ll now, ll pre) {
    node_num[now] += 1;

    for(auto nx: G[now]) {
        if (nx == pre) continue;
        dfs(nx, now);
        node_num[now] += node_num[nx];
    }
}

void solve() {
    ll N; cin >> N;
    G.resize(N);
    for(int i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }

    // 各辺の貢献度の合計が求める答え
    // 辺の貢献度 = 辺を通る回数
    node_num.assign(N, 0);
    dfs(0, -1);

    // 答え計算
    ll ans = 0;
    for(ll i=1; i<N; i++) {
        ans += node_num[i]*(N-node_num[i]);
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}