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

template <typename T>
struct UnionFindVerSize {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
        T group_num;  // 連結成分の個数

    public:
        vector<set<ll>> graph;  // graph[i] := 頂点iと隣接している頂点リスト
        UnionFindVerSize(T N=0): sizes(N,1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
            this->group_num = N;
            graph.resize(N);
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

            graph[x].insert(y);
            graph[y].insert(x);
        }

        void disunite(T x, T y) {
            graph[x].erase(y);
            graph[y].erase(x);
        }

        /* xとyの辺を取り除いても連結でいられるか？*/
        bool is_cycle_if_disunite(T x, T y) {
            deque<T> deq;
            set<T> visited;
            deq.push_back(x);
            while(!deq.empty()) {
                T u = deq.front(); deq.pop_front();
                if (visited.count(u)) continue;
                visited.insert(u);

                for(T v: graph[u]) {
                    if (u==x && v==y) continue;
                    if (visited.count(v)) continue;
                    if (v == y) {
                        return true;
                    }
                    deq.push_back(v);
                }
            }
            return false;
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

struct edge {long long u, v, cost; };  // 頂点uと頂点vを結ぶ無向辺（コスト：cost）

bool comp(const edge& e1, const edge& e2) {
    return e1.cost < e2.cost;
}

pair<UnionFindVerSize<long long>, long long> kruskal(vector<edge> es, long long V, long long E) {
    sort(es.begin(), es.end(), comp);  // edge.costが小さい順にソートする
    UnionFindVerSize uf = UnionFindVerSize<long long>(V);

    long long res = 0;  // 最小全域木のコスト
    for (long long i=0; i<E; i++) {
        edge e = es[i];
        if (!uf.is_same_group(e.u, e.v)) {
            uf.unite(e.u, e.v);
            res += e.cost;
        }
    }
    return {uf, res};
}

pair<UnionFindVerSize<long long>, long long> kruskal2(vector<edge> es, long long V, long long E, const vector<edge> &connected, const set<pair<ll,ll>> &disconnected) {
    sort(es.begin(), es.end(), comp);  // edge.costが小さい順にソートする
    UnionFindVerSize uf = UnionFindVerSize<long long>(V);
    long long res = 0;  // 最小全域木のコスト

    // すでに接続してるものがあるので、それは必ず使う
    for(edge e: connected) {
        uf.unite(e.u, e.v);
        res += e.cost;
    }

    for (long long i=0; i<E; i++) {
        edge e = es[i];
        if (disconnected.count({e.u, e.v})) continue;

        if (!uf.is_same_group(e.u, e.v)) {
            uf.unite(e.u, e.v);
            res += e.cost;
        }
    }
    return {uf, res};
}

/* 2点間のユークリッド距離を整数に四捨五入する計算 */
ll distance(ll x1, ll y1, ll x2, ll y2) {
    return (ll)round(sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

/* [d, 3d]の区間でランダムに返す */
ll rand_distance(ll d) {
    // 疑似乱数を使ったかなり雑な実装
    ll h = (3*d - d) + 1;
    ll r = (ll)rand();
    if (r%2==0) {
        return 2*d + r%(h/2);
    }
    else {
        return 2*d - r%(h/2);
    }
}

// [d, 3d]の連続一様分布と仮定する
bool calc_confidence_interval(ll d) {
    ll mu = (4*d)/2;  // 平均
    double sigma2 = (double)(2*d)*(2*d)/12;  // 分散
    double sigma = sqrt(sigma2);

    double res = (double)(d - mu) / sigma;
    double p = 1.96;
    return (-p <= res && res <= p);
}


// 並行世界を作る戦略
// TLE
void solve() {
    // random_device rnd;
    // mt19937 mt(rnd());
    ll N = 400, M = 1995;
    // ll MAX_DISTANCE = distance(0,0,800,800);

    vector<ll> X(N), Y(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i];
    }

    ll WORLD_NUM = 3;  // 19
    vector<vector<edge>> world(WORLD_NUM, vector<edge>(M));  // 並行世界を作る
    for(ll i=0; i<M; i++) {
        ll u, v;
        cin >> u >> v;
        ll d = distance(X[u], Y[u], X[v], Y[v]);
        // uniform_int_distribution<> myrand(d, 3*d);

        for(ll w=0; w<WORLD_NUM; w++) {
            edge e = {u, v, rand_distance(d)};
            // edge e = {u, v, (ll)myrand(mt)};  // ランダムに[d, 3d]に設定
            // edge e = {u, v, 2*d};
            world[w][i] = e;
        }
    }

    // 毎回クラスカルする
    vector<edge> connected;   // 接続することが決まった辺
    set<pair<ll,ll>> disconnected;  // 接続しないことが決まった辺
    for(ll i=0; i<M; i++) {  // O(M)
        ll l; cin >> l;
        ll u = world[0][i].u;
        ll v = world[0][i].v;

        // 並行世界で多数決を採る
        ll vote = 0;  // 投票数
        for(ll w=0; w<WORLD_NUM; w++) {
            world[w][i] = {u, v, l};
            auto [kruskal_uf, kruskal_cost] = kruskal2(world[w], N, M, connected, disconnected); // O(M logN)?

            if (kruskal_uf.graph[u].count(v)) {
                vote++;
            }
        }

        // 過半数を越えてたら辺を採択
        if (vote > WORLD_NUM/2) {
            cout << "1" << endl << flush;
            connected.push_back({u, v, l});
        }
        else {
            cout << "0" << endl << flush;
            disconnected.insert({u, v});
        }
    }
}


int main() {
    solve();
    return 0;
}