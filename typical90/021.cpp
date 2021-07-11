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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

ll N, M;
vector<ll> id2sccid;  // 強連結成分（SCC）用に記録する番号(頂点番号→SCCID)
vector<ll> sccid2id;  // SCCIDから頂点番号を割り出すテーブル（SCCID→頂点番号）
vector<set<ll>> paths;      // paths[u] := 頂点uに隣接している頂点
vector<set<ll>> rev_paths;  // 辺の向きをすべて反転させたやつ
vector<bool> step2_done;  // ステップ2で終了したSCCIDを記録する

void dfs_step1(ll u, ll &sccid, set<ll> &visited) {
    if (visited.count(u)) return;
    if (id2sccid[u]!=-1) return;
    visited.insert(u);

    for(auto v: paths[u]) {
        dfs_step1(v, sccid, visited);
    }

    id2sccid[u] = sccid;
    sccid2id[sccid] = u;
    sccid++;
}

void dfs_step2(ll u, set<ll> &visited) {
    if (visited.count(u)) return;
    if (step2_done[id2sccid[u]]) return;
    visited.insert(u);
    step2_done[id2sccid[u]] = true;

    for(auto v: rev_paths[u]) {
        dfs_step2(v, visited);
    }
}

void solve() {
    cin >> N >> M;
    id2sccid.resize(N, -1);
    sccid2id.resize(N, -1);
    paths.resize(N);
    rev_paths.resize(N);
    for(int i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        paths[a].insert(b);
        rev_paths[b].insert(a);
    }

    // [ステップ1]
    // DFSの帰りがけ順に番号を振る
    ll sccid = 0; // SCCでつける番号
    for(int u=0; u<N; u++) {
        set<ll> visited;
        dfs_step1(u, sccid, visited);
    }

    // [ステップ2]
    // 辺の向きをすべて反転させ、番号の大きい順からDFSする
    // （実装のコツ）SCC用の番号i=N-1から順に、「反転させた有向辺が張っているならグループ化」をDFSでやっていく
    step2_done.resize(N, false);
    set<set<ll>> scc_groups;  // 強連結成分のグループ
    for(int i=N-1; i>=0; i--) {
        if (step2_done[i]) continue;
        set<ll> visited;
        dfs_step2(sccid2id[i], visited);
        scc_groups.insert(visited);
    }

    // 答えを出力
    ll ans = 0;
    for(auto group: scc_groups) {
        ll n = group.size();
        ans += n*(n-1)/2;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}