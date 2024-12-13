#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


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
    ll N, M, K; cin >> N >> M >> K;
    vector<tuple<ll,ll,ll>> edges(M);
    for(ll i=0; i<M; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        edges[i] = {w,u,v};
    }
    sort(edges.begin(), edges.end());

    vector<ll> A(N), B(N); // 個数
    for(ll i=0; i<K; i++) {
        ll a; cin >> a;
        a--;
        A[a]++;
    }
    for(ll i=0; i<K; i++) {
        ll b; cin >> b;
        b--;
        B[b]++;
    }

    ll ans = 0;
    UnionFindVerSize<ll> uf(N);
    for(auto[c,u,v]: edges) {
        if (uf.is_same_group(u,v)) continue;
        u = uf.find_root(u);
        v = uf.find_root(v);
        if (A[v]>=1) swap(u,v);
        if (A[u]!=0 and B[v]!=0) {
            // マッチングできる場合
            ll x = min(A[u], B[v]);
            ans += c*x;
            A[u] -= x; B[v] -= x;
        }
        ll sumA = A[u]+A[v];
        ll sumB = B[u]+B[v];
        uf.unite(u,v);
        A[uf.find_root(u)] = sumA;
        B[uf.find_root(v)] = sumB;
    }
    cout << ans << endl;
}

void solve2() {
    ll N, M, K; cin >> N >> M >> K;
    vector<tuple<ll,ll,ll>> edges(M);
    for(ll i=0; i<M; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        edges[i] = {w,u,v};
    }
    sort(edges.begin(), edges.end());

    vector<ll> A(N), B(N); // 個数
    for(ll i=0; i<K; i++) {
        ll a; cin >> a;
        a--;
        A[a]++;
    }
    for(ll i=0; i<K; i++) {
        ll b; cin >> b;
        b--;
        B[b]++;
    }

    ll ans = 0;
    UnionFindVerSize<ll> uf(N);
    for(auto[w,u,v]: edges) {
        if (uf.is_same_group(u,v)) continue;

        for(ll i=0; i<2; i++) {
            u = uf.find_root(u);
            v = uf.find_root(v);
            ll mn = min(A[u], B[v]);
            ans += w*mn;
            A[u]-=mn; B[v]-=mn;
            swap(u,v);
        }

        uf.unite(u,v);
        ll sumA = A[u] + A[v];
        ll sumB = B[u] + B[v];
        A[uf.find_root(u)] = sumA;
        B[uf.find_root(v)] = sumB;
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}