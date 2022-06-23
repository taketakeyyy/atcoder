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
    vector<set<pair<ll,ll>>> G(N);  // {行き先番号, 辺id}
    vector<ll> C(M);

    // d2 + d3 + ... は、頂点2への最短路 + 頂点3への最短路 + ...
    // クラスカル法は辺の最小値
    // 頂点の最短路を頂点のコストと考えると、ダイクストラ法で解ける？
    for(ll i=0; i<M; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        G[a].insert({b, i});
        G[b].insert({a, i});
        C[i] = c;
    }

    vector<ll> from(N, -1);  // from[i] := 頂点iは、どの頂点から来たのか
    vector<ll> dist(N, INF);  // dist[i] := 頂点0から頂点iまでの最短距離
    dist[0] = 0;
    priority_queue<tuple<ll,ll>, vector<tuple<ll,ll>>, greater<tuple<ll,ll>>> pq;  // 昇順  {cost, 頂点番号}
    pq.push({0, 0});
    while(!pq.empty()) {
        auto[cost, u] = pq.top(); pq.pop();

        if (dist[u] < cost) {
            continue;
        }

        for(auto [v, eid]: G[u]) {
            if (dist[v] > dist[u] + C[eid]) {
                dist[v] = dist[u] + C[eid];
                pq.push({dist[v], v});
                from[v] = u;
            }
        }
    }

    // from を使って、答えを作成
    deque<ll> deq; deq.push_back(0);
    while(!deq.empty()) {
        ll u = deq.front(); deq.pop_front();

        for(auto [v, eid]: G[u]) {
            if (from[v] != u) continue;
            deq.push_back(v);
            cout << eid+1 << " ";
        }
    }
    cout << endl;

}


int main() {
    solve();
    return 0;
}