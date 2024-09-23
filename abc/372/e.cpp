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
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
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
        vector<set<T>> usets; // usets[i] := グループiが連結な頂点集合

    public:
        UnionFindVerSize(T N=0): sizes(N,1), parents(N), usets(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
                this->usets[i].insert(i);
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
                this->usets[gy].merge(this->usets[gx]);
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
                this->usets[gx].merge(this->usets[gy]);
            }
            this->group_num--;
        }

        // クエリ応答
        void query(ll v, ll k) {
            ll gv = this->find_root(v);
            if ((ll)this->usets[gv].size() < k) {
                cout << -1 << endl;
                return;
            }
            else {
                auto it = this->usets[gv].end();
                it--;
                for(ll i=0; i<k-1; i++) it--;

                cout << (*it)+1 << endl;
                return;
            }
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

void solve() {
    ll N, Q; cin >> N >> Q;

    UnionFindVerSize<ll> uf(N);
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            ll u, v; cin >> u >> v;
            u--; v--;
            uf.unite(u,v);
        }
        else {
            ll v, k; cin >> v >> k;
            v--;
            uf.query(v, k);
        }
    }
}


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
struct UnionFindVerSize2 {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
        T group_num;  // 連結成分の個数
        vector<ordered_set<T>> usets; // usets[i] := グループiが連結な頂点集合

    public:
        UnionFindVerSize2(T N=0): sizes(N,1), parents(N), usets(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
                this->usets[i].insert(i);
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
                // this->usets[gy].merge(this->usets[gx]); // mergeメソッドがない！
                for(ll v: this->usets[gx]) {
                    this->usets[gy].insert(v);
                }
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
                // this->usets[gx].merge(this->usets[gy]); // mergeメソッドがない！
                for(ll v: this->usets[gy]) {
                    this->usets[gx].insert(v);
                }
            }
            this->group_num--;
        }

        // クエリ応答
        void query(ll v, ll k) {
            ll gv = this->find_root(v);
            if ((ll)this->usets[gv].size() < k) {
                cout << -1 << endl;
                return;
            }
            else {
                k--;
                ll N = this->usets[gv].size();
                auto itr = this->usets[gv].find_by_order(N-1-k); // find_by_order(k) := (0-indexed)k番目に小さい値を指すイテレータを返す
                cout << (*itr)+1 << endl;
                return;
            }
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

void solve2() {
    ll N, Q; cin >> N >> Q;

    UnionFindVerSize2<ll> uf(N);
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            ll u, v; cin >> u >> v;
            u--; v--;
            uf.unite(u,v);
        }
        else {
            ll v, k; cin >> v >> k;
            v--;
            uf.query(v, k);
        }
    }
}

int main() {
    // solve();
    solve2();
    return 0;
}