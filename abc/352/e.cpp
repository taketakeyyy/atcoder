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

/***クラスカル法
 * Descriptions:
 *  最小全域木と、最小全域木のコストを求める
 * Returns:
 *  pair<UnionFind, long long>
 *   最小全域木(UnionFind)
 *   最小全域木のコスト(long long)
 * Notes:
 *  クラスカル法自体の計算量はO(|E| log|V|)
 *  ただし内部でUnionFindを実行している
 ***/
struct Edge {long long u, v, cost; };  // 頂点uと頂点vを結ぶ無向辺（コスト：cost）
bool comp(const Edge& e1, const Edge& e2) {
    return e1.cost < e2.cost;
}

pair<UnionFindVerSize<long long>, long long> kruskal(vector<Edge> es, long long V) {
    sort(es.begin(), es.end(), comp);  // Edge.costが小さい順にソートする
    UnionFindVerSize uf = UnionFindVerSize<long long>(V);

    long long res = 0;  // 最小全域木のコスト
    for (long long i=0; i<(long long)es.size(); i++) {
        Edge e = es[i];
        if (!uf.is_same_group(e.u, e.v)) {
            uf.unite(e.u, e.v);
            res += e.cost;
        }
    }
    return {uf, res};
}


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> K(M), C(M);
    vector<vector<ll>> A(M);
    vector<pair<ll,ll>> edges(M); // (辺のコスト, 操作番号)
    for(ll m=0; m<M; m++) {
        cin >> K[m] >> C[m];
        edges[m] = {C[m], m};
        A[m].resize(K[m]);
        for(ll i=0; i<K[m]; i++) {
            cin >> A[m][i]; A[m][i]--;
        }
    }

    // 辺をコストが小さい順にソート
    sort(edges.begin(), edges.end());

    // クラスカル法
    UnionFindVerSize<ll> uf(N);
    ll totalCost = 0;
    for(auto[cost, m]: edges) { // O(M)
        ll u = A[m][0];
        for(ll i=1; i<K[m]; i++) { // ループ内合計で4e5
            ll v = A[m][i];
            if (!uf.is_same_group(u, v)) {
                uf.unite(u, v);
                totalCost += cost;
            }
        }
    }

    // 答え
    if (uf.get_group_num() == 1LL) {
        cout << totalCost << endl;
    }
    else {
        cout << -1 << endl;
    }
}


int main() {
    solve();
    return 0;
}