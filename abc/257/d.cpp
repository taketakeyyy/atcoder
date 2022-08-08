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


bool f(ll s, ll N, vector<tuple<ll,ll,ll>> &jumps) {
    // dist[i][j] := 頂点iから頂点jへの最短距離（INFは到達不能）
    vector<vector<ll>> dist(N, vector<ll>(N, 0));
    for(ll i=0; i<N; i++) {
        auto[x1, y1, p1] = jumps[i];
        for(ll j=0; j<N; j++) {
            if (i == j) continue;
            auto[x2, y2, p2] = jumps[j];
            ll d = abs(x1-x2) + abs(y1-y2);
            if (p1*s >= d) {
                dist[i][j] = 1;
            }
            else {
                dist[i][j] = INF;
            }
        }
    }

    // ワーシャルフロイド
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][k]==INF || dist[k][j]==INF) {}  // オーバーフロー対策 (INF+INFだめ)
                else {
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
    }

    // 適切な始点を選べば全点行けるか？
    for(ll i=0; i<N; i++) {
        bool is_ok = true;
        for(ll j=0; j<N; j++) {
            if (dist[i][j] == INF) {
                is_ok = false;
                break;
            }
        }
        if (is_ok) return true;
    }
    return false;
}

void solve1() {
    ll N; cin >> N;
    vector<tuple<ll,ll,ll>> jumps(N);
    for(ll i=0; i<N; i++) {
        ll x, y, p; cin >> x >> y >> p;
        jumps[i] = {x, y, p};
    }

    // sをにぶたんしながらワーシャルフロイド
    ll ls = 1;
    ll rs = 4e9+1;
    while(rs-ls != 1) {
        ll s = (ls+rs)/2;
        bool is_ok = f(s, N, jumps);
        if (is_ok) {
            rs = s;
        }
        else {
            ls = s;
        }
    }
    if (f(ls, N, jumps)) {
        cout << ls << endl;
    }
    else {
        cout << rs << endl;
    }
}

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

/***
 *  UnionFindVerSize
 *
 * Descriptions:
 *  UnionFindのサイズバージョン
 *  グループの併合のとき、サイズが大きい方が、小さい方を併合する
 *  競プロでは、ノードの個数やグループの最小値とかを求めるので、こちらを使うことが多い
 *
 * Args
 *  N(T): N個のノードのUnionFindを作成する
 *
 * ならし計算量
 *  O(α(N))
 *    - α(N)はアッカーマン関数
 *    - 相当小さい（logより小さい）
 ***/
template <typename T>
struct UnionFindVerSize {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
        T group_num;  // 連結成分の個数

    public:
        UnionFindVerSize(T N=0): sizes(N,1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
            this->group_num = N;
        }

        T find_root(T x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(T x, T y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            T gx = this->find_root(x); T gy = this->find_root(y);
            if (gx == gy) return;

            // 深い方が浅い方を併合する（木の偏りが減るので）
            if (this->sizes[gx] < this->sizes[gy]) {
                this->parents[gx] = gy;
                this->sizes[gy] += this->sizes[gx];
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
            }
            this->group_num--;
        }

        T get_size(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }

        bool is_same_group(T x, T y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        T get_group_num() {
            /* 連結成分の個数を返す */
            return this->group_num;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (T i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (T i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};

bool f2(ll s, const ll N, const vector<tuple<ll,ll,ll>> &jumps) {
    vector<set<ll>> G(N);  // G[i] := 頂点iから到達可能な頂点集合
    vector<set<ll>> invG(N);  // invG[i] := G[i]の反転グラフ
    UnionFindVerSize<ll> uf(N);  // UnionFind（連結成分を調べる用）
    for(ll i=0; i<N; i++) {
        auto [x1, y1, p1] = jumps[i];
        for(ll j=0; j<N; j++) {
            if (i == j) continue;
            auto [x2, y2, p2] = jumps[j];
            ll d = abs(x1-x2)+abs(y1-y2);
            if (s*p1 >= d) {
                G[i].insert(j);
                invG[j].insert(i);
                uf.unite(i,j);
            }
        }
    }

    // SCCしてDAGを考える
    SCC<ll> scc = SCC<ll>(N, G);
    auto scc_groups = scc.scc_groups();

    // 根の数を数える
    ll root_num = 0;
    for(auto group: scc_groups) {
        bool is_root = true;
        for(ll u: group) {
            for(ll v: invG[u]) {
                if (!group.count(v)) { is_root = false; break; }
            }
            if (!is_root) break;
        }
        if (is_root) { root_num++; }
    }

    // 根の数が1で、連結成分が1ならば、根から出発すればOK
    if (root_num==1 && uf.get_group_num()==1) {
        return true;
    }
    else {
        return false;
    }
}

void solve2() {
    ll N; cin >> N;
    vector<tuple<ll,ll,ll>> jumps(N);
    for(ll i=0; i<N; i++) {
        ll x, y, p; cin >> x >> y >> p;
        jumps[i] = {x, y, p};
    }

    // sを二分探索しながらグラフを作る。
    // SCC後のDAGグラフで根が1つかつ連結成分が1なら、根からならどこでも到達可能
    ll ls = 1;
    ll rs = 4e9+1;
    while(rs-ls != 1) {
        ll s = (ls+rs)/2;
        bool is_ok = f2(s, N, jumps);
        if (is_ok) {
            rs = s;
        }
        else {
            ls = s;
        }
    }
    if (f2(ls, N, jumps)) {
        cout << ls << endl;
    }
    else {
        cout << rs << endl;
    }
}


int main() {
    // solve1();
    solve2();
    return 0;
}