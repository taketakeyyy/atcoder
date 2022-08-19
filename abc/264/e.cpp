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

void solve() {
    ll N, M, E; cin >> N >> M >> E;
    vector<pair<ll,ll>> Edge(E);  // Edge[i] := 電線iが結ぶ地点{u,v}
    for(ll i=0; i<E; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        Edge[i] = {u,v};
    }

    // クエリ先読み
    ll Q; cin >> Q;
    vector<ll> query(Q);
    set<ll> query_set;
    for(ll q=0; q<Q; q++) {
        ll x; cin >> x; x--;
        query[q] = x;
        query_set.insert(x);
    }

    // クエリを逆順に処理して、辺をつなげていく
    // 最初は、クエリでつなげる辺以外をつなげておく
    UnionFindVerSize<ll> uf(N+M);
    for(ll i=0; i<E; i++) {
        if (query_set.count(i)) continue;
        auto [u, v] = Edge[i];
        uf.unite(u,v);
    }

    // UFのグループ（連結成分）毎に、都市の数と発電所の有無を調べる
    map<ll,ll> group_city_num;  // グループごとの都市の数
    map<ll,bool> group_exist_plant;  // グループごとの発電所の有無
    for(ll i=0; i<N+M; i++) {
        ll root = uf.find_root(i);

        if (i < N) {
            group_city_num[root]++;
        }
        else {
            group_exist_plant[root] = true;
        }
    }

    // 初期解の電気が通っている都市の数を数える
    vector<ll> ans(1, 0);
    for(auto[key, val]: group_city_num) {
        if (group_exist_plant[key]) {
            ans[0] += group_city_num[key];
        }
    }

    // クエリを逆順に処理して地点をつなげていく
    for(ll q=Q-1; q>=1; q--) {
        ll x = query[q];
        auto[u,v] = Edge[x];

        if (!uf.is_same_group(u,v)) {
            // 異なるグループならば
            ll root_u = uf.find_root(u);
            ll root_v = uf.find_root(v);

            // 連結前の都市の数
            ll root_u_city_num = group_city_num[root_u];
            ll root_v_city_num = group_city_num[root_v];

            // 連結前の発電所の存在
            bool root_u_exist_plant = group_exist_plant[root_u];
            bool root_v_exist_plant = group_exist_plant[root_v];

            uf.unite(u,v);
            ll root = uf.find_root(u);

            // 連結後の都市の数
            ll new_num = root_u_city_num;
            new_num += root_v_city_num;
            group_city_num.erase(root_u);
            group_city_num.erase(root_v);
            group_city_num[root] = new_num;

            // 連結後の発電所の存在
            bool new_exist_plant = root_u_exist_plant;
            new_exist_plant |= root_v_exist_plant;
            group_exist_plant.erase(root_u);
            group_exist_plant.erase(root_v);
            group_exist_plant[root] = new_exist_plant;

            // 連結後の電気が通っている都市の数
            ll total = ans[ans.size()-1];
            if (group_exist_plant[root]) {
                if (!root_u_exist_plant) {
                    total += root_u_city_num;
                }
                if (!root_v_exist_plant) {
                    total += root_v_city_num;
                }
            }
            ans.push_back(total);
        }
        else {
            // 既に同じグループならば
            uf.unite(u, v);
            ll total = ans[ans.size()-1];
            ans.push_back(total);
        }
    }

    // 出力
    for(ll i=(ll)ans.size()-1; i>=0; i--) {
        cout << ans[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}