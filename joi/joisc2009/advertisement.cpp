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

class SCC {
    private:
        long long N;  // 頂点数
        vector<set<long long>> graph;  // graph[u] := 頂点uに隣接している頂点vの集合（uからvへの有向辺）
        vector<set<long long>> rev_graph;  // graphの有向辺を反転させたグラフrev_graph
        vector<long long> id2sccid;  // 強連結成分（SCC）用に記録する番号(頂点番号→SCCID)
        vector<long long> sccid2id;  // SCCIDから頂点番号を割り出すテーブル（SCCID→頂点番号）

        void fix_rev_graph() {
            /*** graphの有向辺を反転させたグラフrev_graphを確定させる
             * O(頂点数+辺数)
             ***/
            this->rev_graph.assign(this->N, set<long long>());
            for(long long u=0; u<this->N; u++) {
                for(auto v: graph[u]) {
                    this->rev_graph[v].insert(u);
                }
            }
        }

        void dfs_step1(long long u, long long &sccid, set<long long> &visited) {
            if (visited.count(u)) return;
            if (id2sccid[u]!=-1) return;
            visited.insert(u);

            for(auto v: this->graph[u]) {
                dfs_step1(v, sccid, visited);
            }

            id2sccid[u] = sccid;
            sccid2id[sccid] = u;
            sccid++;
        }

        void dfs_step2(long long u, set<long long> &visited, vector<bool> &step2_done) {
            if (visited.count(u)) return;
            if (step2_done[id2sccid[u]]) return;
            visited.insert(u);
            step2_done[id2sccid[u]] = true;

            for(auto v: this->rev_graph[u]) {
                dfs_step2(v, visited, step2_done);
            }
        }


    public:
        SCC(long long N, vector<set<long long>> graph) {
            this->N = N;
            this->graph = graph;
            this->id2sccid.assign(N, -1);
            this->sccid2id.assign(N, -1);
        }

        set<set<long long>> scc_groups() {
            /* SCCを実行
            Return:
                scc_groups(set<set<long long>>): 強連結成分のグループ
            Notes:
                計算量O(頂点数+辺数)
            */

            // [ステップ1]
            // DFSの帰りがけ順に番号を振る
            long long sccid = 0; // SCCでつける番号
            for(int u=0; u<N; u++) {
                set<long long> visited;
                this->dfs_step1(u, sccid, visited);
            }

            // [ステップ2]
            // 辺の向きをすべて反転させ、番号の大きい順からDFSする
            // （実装のコツ）SCC用の番号i=N-1から順に、「反転させた有向辺が張っているならグループ化」をDFSでやっていく
            this->fix_rev_graph();
            vector<bool> step2_done(this->N, false);  // ステップ2で終了したSCCIDを記録する
            set<set<long long>> scc_groups;  // 強連結成分のグループ
            for(int i=N-1; i>=0; i--) {
                if (step2_done[i]) continue;
                set<long long> visited;
                dfs_step2(sccid2id[i], visited, step2_done);
                scc_groups.insert(visited);
            }

            return scc_groups;
        }

        void print_scc_groups(set<set<long long>> &scc_groups) {
            /* scc_groupsの中身を見る */
            auto itr = scc_groups.begin();
            for(int i=0; i<scc_groups.size(); i++) {
                cout << "group" << i << " (size: " << (*itr).size() << "): ";
                for(auto u: *itr) {
                    cout << u << " ";
                }
                cout << endl;
                itr++;
            }
        }
};


void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    vector<ll> indeg(N, 0);  // 入次数
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        G[a].insert(b);
        indeg[b]++;
    }

    // 強連結成分分解(SCC)を使って同じグループの頂点を一つにまとめると、サイクルを含まないDAGになる
    // DAGの根（入次数0の頂点）の個数が答え。
    SCC scc(N, G);
    auto scc_groups = scc.scc_groups();

    ll ans = 0;
    // SCCのグループは1つの頂点とみなす
    for(auto group: scc_groups) {
        // グループ内同士の有向辺ぶんだけ入次数をへらす
        for(auto u: group) {
            for(auto v: G[u]) {
                if (!group.count(v)) { continue; }
                indeg[v]--;
            }
        }
        // グループ内のすべての頂点の入次数が0なら根となる
        bool is_root = true;
        for(auto u: group) {
            if (indeg[u] != 0) { is_root = false; break; }
        }
        if (is_root) { ans++; }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}