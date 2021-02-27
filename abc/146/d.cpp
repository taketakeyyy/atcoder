#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

ll N;
vector<vector<ll>> G;  // 木
map<pair<ll,ll>,ll>color;

void dfs(ll u, ll parent_c) {
    ll c = 1;
    for(auto v: G[u]) {
        if (c == parent_c) c++;
        color[make_pair(u,v)] = c;
        dfs(v, c);
        c++;
    }
}

void solve(){
    cin >> N;
    G.resize(N);
    vector<pair<ll,ll>> edges;  // 辺の順番を覚えておく
    map<ll,ll> jisu;  // 頂点の次数
    ll mx_jisu = 0;  // 最大次数
    for(int i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        jisu[a]++; jisu[b]++;
        mx_jisu = max(mx_jisu, max(jisu[a], jisu[b]));
        G[a].push_back(b);
        edges.push_back(make_pair(a,b));
    }

    // 必要な色の数は頂点の最大次数
    // どうやって辺の色を塗っていくか？
    // 根から順番に、DFS（またはBFS）で部分木に対して塗っていく
    dfs(0, -1);

    cout << mx_jisu << endl;
    for (int i=0; i<N-1; i++) {
        cout << color[edges[i]] << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}