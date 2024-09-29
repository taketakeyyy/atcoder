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
//ordered_set
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
    ll N, M; cin >> N >> M;
    vector<vector<pair<ll,ll>>> G(N);
    vector<vector<pair<ll,ll>>> invG(N);
    vector<ll> indeg(N, 0); // 入次数
    UnionFindVerSize<ll> uf(N);
    for(ll i=0; i<M; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        G[u].push_back({v,w});
        invG[v].push_back({u,w});
        indeg[v]++;
        uf.unite(u,v);
    }

    vector<ll> ans(N, 0LL);
    vector<bool> visited(N, false);
    auto f = [&](ll s) {
        deque<ll> deq; deq.push_back(s);
        visited[s] = true;

        while(!deq.empty()) {
            ll u = deq.front(); deq.pop_front();

            for(auto[v, w]: G[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                ans[v] = ans[u] + w;
                deq.push_back(v);
            }
            for(auto[v, w]: invG[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                ans[v] = ans[u] - w;
                deq.push_back(v);
            }
        }
    };

    // 各連結成分ごとに処理する
    for(ll u=0; u<N; u++) {
        if (uf.find_root(u) == u) {
            f(u);
        }
    }

    const ll MAXV = 1e18;
    //範囲内に収まっているか？
    {
        ll margin = -INF;
        for(ll i=0; i<N; i++) {
            if (ans[i] < -MAXV) {
                chmax(margin, -MAXV-ans[i]);
            }
        }
        if (margin != -INF) {
            for(ll i=0; i<N; i++) {
                ans[i] += margin;
            }
        }
    }
    {
        ll margin = -INF;
        for(ll i=0; i<N; i++) {
            if (ans[i] > MAXV) {
                chmax(margin, ans[i]-MAXV);
            }
        }
        if (margin != -INF) {
            for(ll i=0; i<N; i++) {
                ans[i] -= margin;
            }
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}