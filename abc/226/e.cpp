#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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
        vector<T> edges;   // グループの辺の数
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
        T group_num;

    public:
        set<T> cycles;
        UnionFindVerSize(T N=0): sizes(N,1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
            this->group_num = N;
            this->edges.resize(N, 0);
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

            if (gx == gy) {
                // (★1) すでに同じグループに所属しているので、サイクル発生
                this->cycles.insert(gx);
                this->edges[gx]++;
                return;
            }

            // (★2)併合するときに、片方がサイクルだったら、併合後もサイクルになる
            bool flag_cycle = false;
            if (this->is_cycle(gx) || this->is_cycle(gy)) {
                flag_cycle = true;
                this->cycles.erase(gx);  // 消しとく
                this->cycles.erase(gy);  // 消しとく
            }

            // 深い方が浅い方を併合する（木の偏りが減るので）
            ll g;
            if (this->sizes[gx] < this->sizes[gy]) {
                this->parents[gx] = gy;
                this->sizes[gy] += this->sizes[gx];
                g = gy;
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
                g = gx;
            }
            this->group_num--;

            this->edges[g] = this->edges[gx] + this->edges[gy] + 1;

            if (flag_cycle) {
                this->cycles.insert(g);  // (★2)併合後もサイクル
            }
        }

        bool is_cycle(T x) {
            T gx = this->find_root(x);
            return (bool)this->cycles.count(gx);
        }

        T get_size(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }
        T get_edge(T x) {
            return this->edges[this->find_root(x)];
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

ll N, M;
vector<set<ll>> G;

void solve() {
    // 各連結成分について、頂点数=辺数 が成り立つことが条件
    cin >> N >> M;
    G.resize(N);
    UnionFindVerSize<ll> uf = UnionFindVerSize<ll>(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].insert(v);
        G[v].insert(u);
        uf.unite(u,v);
    }

    set<ll> groups;  // 各連結成分の親のみを格納
    for(ll i=0; i<N; i++) {
        if (uf.find_root(i) == i) {
            groups.insert(i);
        }
    }

    ll ans = 1;
    for(ll u: groups) {
        if (uf.get_edge(u) == uf.get_size(u)) {
            ans *= 2;
            ans %= MOD;
        }
        else {
            cout << 0 << endl;
            return;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}