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


/**
 * @brief 二次元座標のKD木。二次元座標の領域内にある点を取得したりする。
 *
 * @tparam T int, long long
 */
template<typename T>
class KDTree {
    public:
        static const T NIL = -1;  // 意味のない値
        /**
         * @brief KDTreeの木構造用ノード
         */
        class Node{
            public:
                T location;  // 位置
                T p, l, r;  // 親, 左の子, 右の子
                Node(){}
        };
        /**
         * @brief 座標クラス
         */
        class Point{
            public:
                T id, x, y;  // 頂点番号, x座標, y座標
                Point(){}
                Point(T id, T x, T y): id(id),x(x),y(y){}
                bool operator<(const Point &p)const{
                    return id < p.id;
                }
        };
        // X座標でソートするための比較関数
        static bool compX(const Point &p1,const Point &p2){return p1.x<p2.x;}
        // Y座標でソートするための比較関数
        static bool compY(const Point &p1,const Point &p2){return p1.y<p2.y;}

    private:
        /**
         * @brief buildメソッドの実態(DFSで構築する)
         *
         * @param l 左の境界値
         * @param r 右の境界値
         * @param depth DFSの深さ
         * @param np ?
         */
        T _build(T l, T r, T depth, T &np) {
            if (!(l<r)) { return NIL; }
            T mid = (l+r)/2;
            T t = np++;
            if (depth%2 == 0) {
                sort(P.begin()+l, P.begin()+r, compX);  // X座標でソート
            }
            else {
                sort(P.begin()+l, P.begin()+r, compY);  // Y座標でソート
            }
            nodes[t].location = mid;
            nodes[t].l = _build(l, mid, depth+1, np);
            nodes[t].r = _build(mid+1, r, depth+1, np);
            return t;
        }

        /**
         * @brief findメソッドの実態
         *
         * @param v
         * @param scoord 領域の開始座標(sx, sy)
         * @param tcoord 領域の終了座標(tx, ty)
         * @param depth DFSの深さ
         * @param ans 領域に含まれる点を格納
         */
        void _find(T v, pair<T, T>scoord, pair<T, T> tcoord, T depth, vector<Point> &ans) {
            auto [sx, sy] = scoord;
            auto [tx, ty] = tcoord;
            T x = P[nodes[v].location].x;
            T y = P[nodes[v].location].y;
            if (sx<=x && x<=tx && sy<=y && y<=ty){
                ans.push_back(P[nodes[v].location]);
            }
            if (depth%2 == 0) {
                if (nodes[v].l!=NIL) {
                    if(sx<=x) _find(nodes[v].l,{sx,sy},{tx,ty},depth+1,ans);
                }
                if (nodes[v].r!=NIL) {
                    if(x<=tx) _find(nodes[v].r,{sx,sy},{tx,ty},depth+1,ans);
                }
            }
            else {
                if (nodes[v].l != NIL) {
                    if (sy<=y) _find(nodes[v].l,{sx,sy},{tx,ty},depth+1,ans);
                }
                if (nodes[v].r != NIL) {
                    if (y<=ty) _find(nodes[v].r,{sx,sy},{tx,ty},depth+1,ans);
                }
            }
        }

    public:
        T N;  // 頂点数
        vector<Point> P;  // 点を格納するリスト
        vector<Node> nodes;  // 木構造用のNodeを格納するリスト
        T root;  // 根

        KDTree(){}
        KDTree(T N){init(N);}

        void init(T N_){
            N = N_;
            P.assign(N, Point());
            nodes.assign(N, Node());
        }

        /**
         * @brief kdtreeを構築する。計算量は、ソートしてるので O(N (logN)^2)。
         */
        void build() {
            T np = 0;
            root = _build(0, N, 0, np);
        }

        /**
         * @brief 指定の領域内に含まれる座標（Point）のリストを返す
         *
         * @param scoord 領域の開始座標(sx, sy)
         * @param tcoord 領域の終了座標(tx, ty)
         *
         * @note
         * (sx, sy)●────┐
         *         │    │
         *         └────●(tx, ty)
         */
        vector<Point> find(pair<T, T>scoord, pair<T, T> tcoord) {
            vector<Point> ans;
            _find(root, scoord, tcoord, 0, ans);
            return ans;
        }

        /**
         * @brief 与えられた仲間の座標に最も近いスパイとの距離を返す
         *
         * @param x 仲間のX座標
         * @param y 仲間のY座標
         * @return T スパイとの距離
         */
        T nearest_spy_distance(T x, T y) {
            ll l = 1;
            ll r = 2000000000;
            while(r-l!=1) {
                ll mid = (l+r)/2;
                pair<T, T> s = {max(x-mid,(T)-1000000000), max(y-mid, (T)-1000000000)};
                pair<T, T> t = {min(x+mid,(T)1000000000), min(y+mid,(T)1000000000)};
                auto spys = find(s, t);
                if (spys.size() >= 1) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }
            ll mn = INF;
            pair<T, T> s = {max(x-r,(T)-1000000000), max(y-r,(T)-1000000000)};
            pair<T, T> t = {min(x+r,(T)1000000000), min(y+r,(T)1000000000)};
            auto spys = find(s, t);
            for(auto p: spys) {
                mn = min(mn, (p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
            }
            return mn;
        }

        /**
         * @brief 二次元座標に点を追加する
         *
         * @param id 頂点番号
         * @param x X座標
         * @param y Y座標
         */
        void add_point(T id, T x, T y) {
            P[id] = Point(id, x, y);
            nodes[id].l = nodes[id].r = nodes[id].p = NIL;
        }

        /**
         * @brief nodesを出力する。デバッグ用。
         */
        void print_nodes() {
            for(ll i=0; i<N; i++) {
                cout << "nodes[" << i << "]: ";
                cout << "location=" << nodes[i].location << " ";
                cout << "p=" << nodes[i].p << " ";
                cout << "l=" << nodes[i].l << " ";
                cout << "r=" << nodes[i].r << endl;
            }
        }

        /**
         * @brief Pを出力する。デバッグ用。
         */
        void print_points() {
            for(ll i=0; i<N; i++) {
                cout << "P[" << i << "]: ";
                cout << "id=" << P[i].id << " ";
                cout << "(x, y)=" << "(" << P[i].x << ", " << P[i].y << ")" << endl;
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
    if (M==0) { cout << 1 << endl; return; }
    vector<pair<ll,ll>> S(M);
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        S[i] = {x,y};
    }

    // 制限時間8secなので、O(NM)いける？
    // danger[i] := 仲間iの、最も近いスパイまでの距離
    // vector<ll> danger(N, INF);
    // for(ll i=0; i<N; i++) {
    //     auto [x1, y1] = F[i];
    //     ll mn = INF;
    //     for(ll j=0; j<M; j++) {
    //         auto[x2, y2] = S[j];
    //         mn = min(mn, (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    //     }
    //     danger[i] = mn;
    // }

    // スパイの座標をKD木に乗せる
    KDTree<ll> kd(M);
    for(ll i=0; i<M; i++) {
        kd.add_point(i, S[i].first, S[i].second);
    }
    kd.build();
    vector<ll> danger(N, INF);
    for(ll i=0; i<N; i++) {
        danger[i] = kd.nearest_spy_distance(F[i].first, F[i].second);
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