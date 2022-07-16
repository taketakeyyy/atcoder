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
const long long INF = LONG_LONG_MAX;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


/** 強連結成分分解（SCC）
 * @brief
 * 有向グラフに対して「お互いに行き来できる頂点を同じグループにする」ことを強連結分解（SCC）という。
 *
 * サイクルをグループ分けするイメージ。
 *
 * @tparam T int, long long
 *
 * @param N 頂点数
 * @param G グラフG。G[i] := 頂点iに隣接している頂点集合
 * @example
 * Usage
 *   long long N = 4;
 *   long long M = 7;  // 辺数（使ってない）
 *   vector<set<long long>> graph(N);
 *   graph[0].insert(1);
 *   graph[1].insert(0);
 *   graph[1].insert(2);
 *   graph[3].insert(2);
 *   graph[3].insert(0);
 *   graph[0].insert(3);
 *   graph[1].insert(2);
 *
 *   // SCC実行
 *   SCC scc = SCC<long long>(N, graph);
 *   set<set<long long>> scc_groups = scc.scc_groups();
 *
 *   // SCCを見る
 *   scc.print_scc_groups(scc_groups);
 *   // group0 (size: 3): 0 1 3
 *   // group1 (size: 1): 2
 */
template<typename T>
class SCC {
    private:
        T N;  // 頂点数
        vector<set<T>> graph;  // graph[u] := 頂点uに隣接している頂点vの集合（uからvへの有向辺）
        vector<set<T>> rev_graph;  // graphの有向辺を反転させたグラフrev_graph
        vector<T> id2sccid;  // 強連結成分（SCC）用に記録する番号(頂点番号→SCCID)
        vector<T> sccid2id;  // SCCIDから頂点番号を割り出すテーブル（SCCID→頂点番号）

        /**
         * @brief
         * graphの有向辺を反転させたグラフrev_graphを確定させる。
         * O(頂点数+辺数)。
         */
        void fix_rev_graph() {
            this->rev_graph.assign(this->N, set<T>());
            for(T u=0; u<this->N; u++) {
                for(auto v: graph[u]) {
                    this->rev_graph[v].insert(u);
                }
            }
        }

        void dfs_step1(T u, T &sccid, set<T> &visited) {
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

        void dfs_step2(T u, set<T> &visited, vector<bool> &step2_done) {
            if (visited.count(u)) return;
            if (step2_done[id2sccid[u]]) return;
            visited.insert(u);
            step2_done[id2sccid[u]] = true;

            for(auto v: this->rev_graph[u]) {
                dfs_step2(v, visited, step2_done);
            }
        }


    public:
        SCC(T N, vector<set<T>> graph) {
            this->N = N;
            this->graph = graph;
            this->id2sccid.assign(N, -1);
            this->sccid2id.assign(N, -1);
        }

        /**
         * @brief SCCを実行。
         * 計算量O(頂点数+辺数)。
         * @return set<set<T>> 強連結成分のグループ
         */
        set<set<T>> scc_groups() {
            // [ステップ1]
            // DFSの帰りがけ順に番号を振る
            T sccid = 0; // SCCでつける番号
            for(int u=0; u<N; u++) {
                set<T> visited;
                this->dfs_step1(u, sccid, visited);
            }

            // [ステップ2]
            // 辺の向きをすべて反転させ、番号の大きい順からDFSする
            // （実装のコツ）SCC用の番号i=N-1から順に、「反転させた有向辺が張っているならグループ化」をDFSでやっていく
            this->fix_rev_graph();
            vector<bool> step2_done(this->N, false);  // ステップ2で終了したSCCIDを記録する
            set<set<T>> scc_groups;  // 強連結成分のグループ
            for(int i=N-1; i>=0; i--) {
                if (step2_done[i]) continue;
                set<T> visited;
                dfs_step2(sccid2id[i], visited, step2_done);
                scc_groups.insert(visited);
            }

            return scc_groups;
        }

        /**
         * @brief scc_groupsの中身を見る。
         * @param scc_groups
         * @param idx_plus 頂点番号に足す数。デフォルト0。
         */
        void print_scc_groups(set<set<T>> &scc_groups, T idx_plus=0) {
            auto itr = scc_groups.begin();
            for(size_t i=0; i<scc_groups.size(); i++) {
                cout << "group" << i << " (size: " << (*itr).size() << "): ";
                for(auto u: *itr) {
                    cout << u+idx_plus << " ";
                }
                cout << endl;
                itr++;
            }
        }
};

// https://www.slideshare.net/yumainoue965/arc-010-d-15658062
// * 情報を伝えるのは、有向辺と考えられる。
//   - ある仲間から他の仲間に情報が伝えられるかどうかを判定して、辺を張る
//   - 双方向に辺が張れるとは限らない点に注意
// * 半径は任意に決められるので、一番近いスパイとの距離danよりも近いところにいる仲間なら全て情報が伝えられる
//   - danがわかれば愚直に判定できるので、O(2^n)でグラフが作れる
// * ある仲間から情報を伝えられる仲間は、DFSで調べられる
//   - DFSで訪れることができた仲間には情報を伝えることができる

// * 被覆
//   - 頂点xを始点としてたどり着けるところ = 被覆
// * 最小被覆問題
//   - 頂点集合全体をカバーできる被覆の最小
void solve() {
    ll N; cin >> N;
    if (N==0) { cout << 0 << endl; return; }

    vector<pair<ll,ll>> F(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        F[i] = {x,y};
    }
    ll M; cin >> M;
    vector<pair<ll,ll>> S(M);
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        S[i] = {x,y};
    }

    // dist[i][j] := 仲間iから仲間jの距離（の2乗）
    vector dist(N, vector<ll>(N, 0));
    for(ll i=0; i<N; i++) {
        auto [x1, y1] = F[i];
        for(ll j=0; j<N; j++) {
            auto[x2, y2] = F[j];
            dist[i][j] = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
        }
    }

    // 制限時間8secなので、O(NM)いける？
    // danger[i] := 仲間iの、最も近いスパイまでの距離
    vector<ll> danger(N, INF);
    for(ll i=0; i<N; i++) {
        auto [x1, y1] = F[i];
        ll mn = INF;
        for(ll j=0; j<M; j++) {
            auto[x2, y2] = S[j];
            mn = min(mn, (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        }
        danger[i] = mn;
    }

    // G[i] := 仲間iが情報を伝えられる仲間のリスト
    vector<set<ll>> G(N), invG(N);  // グラフ, 反転グラフ
    for(ll i=0; i<N; i++) {
        auto[x1, y1] = F[i];
        ll dan = danger[i];
        for(ll j=0; j<N; j++) {
            auto[x2, y2] = F[j];
            ll d = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
            if (d < dan) {
                G[i].insert(j);
                invG[j].insert(i);
            }
        }
    }

    // SCCのグループを得る
    SCC<ll> scc(N, G);
    auto scc_groups = scc.scc_groups();

    // SCC後のDAGにおいて、入次数0の頂点（根）を数える
    ll root_num = 0;
    for(auto group: scc_groups) {
        bool is_root = true;
        for(ll u: group) {
            for(ll v: invG[u]) {
                if (!group.count(v)) { is_root = false; break; }
            }
        }
        if (is_root) { root_num++; }
    }

    cout << root_num << endl;
}


int main() {
    solve();
    return 0;
}