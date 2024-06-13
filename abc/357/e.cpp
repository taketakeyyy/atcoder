#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

/** 強連結成分分解（SCC）
 * @brief
 * 有向グラフに対して「お互いに行き来できる頂点を同じグループにする」ことを強連結分解（SCC）という。
 *
 * サイクルをグループ分けするイメージ。
 * 計算量O(V+E)
 *
 * @tparam T int, long long
 *
 * @param N 頂点数
 * @param G グラフG。G[i] := 頂点iに隣接している頂点集合
 * @example
 * Usage
 *   long long N = 4;
 *   long long M = 7;  // 辺数（使ってない）
 *   vector<vector<long long>> G(N);
 *   G[0].push_back(1);
 *   G[1].push_back(0);
 *   G[1].push_back(2);
 *   G[3].push_back(2);
 *   G[3].push_back(0);
 *   G[0].push_back(3);
 *   G[1].push_back(2);
 *
 *   // SCC実行
 *   SCC scc = SCC<long long>(N, G);
 *   auto scc_groups = scc.scc_groups();
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
        vector<vector<T>> G;  // G[u] := 頂点uに隣接している頂点vのリスト（uからvへの有向辺）
        vector<vector<T>> invG;  // Gの有向辺を反転させたグラフ
        vector<T> id2sccid;  // 強連結成分（SCC）用に記録する番号(頂点番号→SCCID)
        vector<T> sccid2id;  // SCCIDから頂点番号を割り出すテーブル（SCCID→頂点番号）

        /**
         * @brief
         * Gの有向辺を反転させたグラフinvGを確定させる。
         * O(頂点数+辺数)。
         */
        void fix_invG() {
            this->invG.assign(this->N, vector<T>());
            for(T u=0; u<this->N; u++) {
                for(auto v: this->G[u]) {
                    this->invG[v].push_back(u);
                }
            }
        }

        void dfs_step1(T u, T &sccid, vector<bool> &visited) {
            if (id2sccid[u]!=-1) return;
            if (visited[u]) return;
            visited[u] = true;

            for(auto v: this->G[u]) {
                dfs_step1(v, sccid, visited);
            }

            id2sccid[u] = sccid;
            sccid2id[sccid] = u;
            sccid++;
        }

        void dfs_step2(T u, vector<T> &group, vector<bool> &step2_done) {
            if (step2_done[id2sccid[u]]) return;
            group.push_back(u);
            step2_done[id2sccid[u]] = true;

            for(auto v: this->invG[u]) {
                dfs_step2(v, group, step2_done);
            }
        }


    public:
        vector<T> id2groupid; // 頂点番号→groupid
        SCC(T _N, vector<vector<T>> _G) {
            this->N = _N;
            this->G = _G;
            this->id2sccid.assign(N, -1);
            this->sccid2id.assign(N, -1);
        }

        /**
         * @brief SCCを実行。
         * 計算量O(頂点数+辺数)。
         * @return vector<vector<T>> 強連結成分のグループ
         */
        vector<vector<T>> scc_groups() {
            // [ステップ1]
            // DFSの帰りがけ順に番号を振る
            {
                T sccid = 0; // SCCでつける番号
                vector<bool> visited(this->N, false);
                for(int u=0; u<N; u++) {
                    this->dfs_step1(u, sccid, visited);
                }
            }

            // [ステップ2]
            // 辺の向きをすべて反転させ、番号の大きい順からDFSする
            // （実装のコツ）SCC用の番号i=N-1から順に、「反転させた有向辺が張っているならグループ化」をDFSでやっていく
            this->fix_invG();
            vector<bool> step2_done(this->N, false);  // ステップ2で終了したSCCIDを記録する
            vector<vector<T>> scc_groups;  // 強連結成分のグループ
            for(int i=N-1; i>=0; i--) {
                if (step2_done[i]) continue;
                vector<T> group;
                dfs_step2(sccid2id[i], group, step2_done);
                scc_groups.push_back(group);
            }

            // id2groupid作成
            id2groupid.assign(N, 0);
            for(T groupid=0; groupid<(T)scc_groups.size(); groupid++) {
                for(T u: scc_groups[groupid]) {
                    id2groupid[u] = groupid;
                }
            }

            return scc_groups;
        }

        /**
         * @brief scc_groupsの中身を見る。
         * @param scc_groups
         * @param idx_plus 頂点番号に足す数。デフォルト0。
         */
        void print_scc_groups(vector<vector<T>> &scc_groups, T idx_plus=0) {
            auto itr = scc_groups.begin();
            for(size_t i=0; i<scc_groups.size(); i++) {
                cout << "groupid" << i << " (size: " << (*itr).size() << "): ";
                for(auto u: *itr) {
                    cout << u+idx_plus << " ";
                }
                cout << endl;
                itr++;
            }
        }

        /**
         * @brief 強連結成分分解後のDAGの根を見つける
         * 根は複数ある場合がある
         * @return vector<T> 根のgroupidのリスト
         */
        vector<T> find_roots(const vector<vector<T>> &scc_groups) {
            // SCC後のDAGの根の判定は、グループ外からグループ内に有向辺が存在しないなら根
            vector<T> roots; // 根のgroupidを格納
            for(T groupid=0; groupid<(T)scc_groups.size(); groupid++) {
                const auto &group = scc_groups[groupid];
                bool is_root = true;
                for(T u: group) {
                    for(T v: this->invG[u]) {
                        if (!count(group.begin(), group.end(), v)) { is_root=false; break; } // vectorのcountなので重いかも
                    }
                    if (!is_root) { break; }
                }
                if (is_root) { roots.push_back(groupid); }
            }
            return roots;
        }

        /**
         * @brief 強連結成分分解後のDAGの葉を見つける
         *
         * @return vector<T> 葉のgroupidリスト
         */
        vector<T> find_leaves(const vector<vector<T>> &scc_groups) {
            // SCC後のDAGの葉の判定は、グループ内からグループ外に有向辺が存在しないなら葉
            vector<T> leaves;  // 葉のgroupid番号を格納
            for(T groupid=0; groupid<(T)scc_groups.size(); groupid++) {
                const auto &group = scc_groups[groupid];
                bool is_leaf = true;
                for(T u: group) {
                    for(T v: this->G[u]) {
                        if (!count(group.begin(), group.end(), v)) { is_leaf = false; break; } // vectorのcountなので重いかも
                    }
                    if (!is_leaf) { break; }
                }
                if (is_leaf) { leaves.push_back(groupid); }
            }
            return leaves;
        }

        /**
         * @brief SCC後のDAGを作る
         * 計算量O(V+E)
         * @param scc_groups
         * @return vector<vector<T>>
         */
        vector<vector<T>> make_dag(const vector<vector<T>> &scc_groups) {
            T GN = scc_groups.size();
            vector<set<T>> dagset(GN); // 辺に重複がないようにsetで持つ
            for(T u=0; u<this->N; u++) {
                for(T v: this->G[u]) {
                    if (id2groupid[u] != id2groupid[v]) {
                        // 異なるグループへの辺を貼る
                        dagset[id2groupid[u]].insert(id2groupid[v]);
                    }
                }
            }

            // vectorに直す
            vector<vector<T>> dag(GN);
            for(T groupid=0; groupid<GN; groupid++) {
                dag[groupid] = vector<T>(dagset[groupid].begin(), dagset[groupid].end());
            }

            return dag;
        }
};


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    vector<vector<ll>> G(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        A[i]--;
        G[i].push_back(A[i]);
    }

    // SCCを作る
    SCC<ll> scc(N, G);
    auto scc_groups = scc.scc_groups();
    ll GN = scc_groups.size();
    auto dag = scc.make_dag(scc_groups);

    // DFSで求める
    vector<ll> dp(GN, 0LL); // dp[gu] := SCCのグループguに所属する頂点の答え
    auto dfs = [&](auto dfs, ll gu) -> void {
        // 終了条件
        if (dp[gu] != 0) return;

        // 次の探索
        for(ll gv: dag[gu]) {
            dfs(dfs, gv);
            dp[gu] += dp[gv];
        }

        // 帰りがけに計算
        dp[gu] += scc_groups[gu].size();
    };
    for(ll groupid=0; groupid<GN; groupid++) {
        dfs(dfs, groupid);
    }

    // 答え
    ll ans = 0;
    for(ll u=0; u<N; u++) {
        ans += dp[scc.id2groupid[u]];
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}