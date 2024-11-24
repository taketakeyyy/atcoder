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
// const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
const long long INF = LONG_LONG_MAX;
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

/***ワーシャルフロイド法
 * 計算量:
 *   O(V**3)
***/
class WarshallFloyd {
    vector<vector<long long>> dist;  // 隣接行列dist[i][j]:=iからjへ行くまでのコスト
    long long v;  // 頂点数

    public:
        WarshallFloyd(long long n) {
            /***
             * Args:
             *  n(long long): 頂点数
             **/
            this->dist.resize(n);
            for (long long i=0; i<n; i++) {
                this->dist[i].resize(n, LONG_LONG_MAX);
            }
            for (long long i=0; i<n; i++) {
                this->dist[i][i] = 0;
            }
            this->v = n;
        }

        long long get_vertex_num() {
            // 頂点数を返す
            return this->v;
        }

        void update(long long u, long long v, long long cost) {
            /*** 隣接行列のコストを更新する
             * Args:
             *   u(long long): 頂点uから
             *   v(long long): 頂点vへの
             *   cost(long long): コストをcostに更新する
             **/
            // 二重辺に注意
            this->dist[u][v] = min(this->dist[u][v], cost);
        }

        vector<vector<long long>> shortest_path() {
            /* 最短距離を計算する */
            for (long long k=0; k<this->v; k++) {
                for (long long i=0; i<this->v; i++) {
                    for (long long j=0; j<this->v; j++) {
                        // if (this->dist[i][k]==LONG_LONG_MAX or this->dist[k][j]==LONG_LONG_MAX) continue;
                        long long ncost = this->dist[i][k]+this->dist[k][j]; if (dist[i][k]>0 && dist[k][j]>0 && ncost < 0) ncost = LONG_LONG_MAX;  // オーバーフロー対策（オーバーフローしたらLONG_LONG_MAXにする）
                        this->dist[i][j] = min(this->dist[i][j], ncost);
                    }
                }
            }
            return this->dist;
        }

        // 辺(u,v)のコストを new_cost に更新
        void update_edge(ll u, ll v, ll new_cost, vector<vector<long long>>& dist) {
            ll N = dist.size();
            for (ll i=0; i<N; i++) {
                for (ll j=0; j<N; j++) {
                    if (dist[i][u]!=INF and dist[v][j]!=INF) {
                        ll updated_dist = dist[i][u] + new_cost + dist[v][j];
                        if (updated_dist < dist[i][j]) {
                            dist[i][j] = updated_dist;
                        }
                    }
                }
            }
        }
};

void solve() {
    ll N, M, Q; cin >> N >> M >> Q;
    vector<tuple<ll,ll,ll>> road(M);
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        road[i] = {a,b,c};
    }

    // クエリ先読み
    vector<tuple<ll,ll,ll>> query(Q);
    unordered_set<ll> stop; // 最初通行止めの道路
    for(ll q=0; q<Q; q++) {
        ll type; cin >> type;
        if (type == 1) {
            ll x; cin >> x; x--;
            query[q] = {1,x,-1};
            stop.insert(x);
        }
        else {
            ll x, y; cin >> x >> y;
            x--; y--;
            query[q] = {2,x,y};
        }
    }

    // ワーシャルフロイド
    WarshallFloyd wf(N);
    for(ll i=0; i<M; i++) {
        if (stop.contains(i)) continue;
        auto[a,b,c] = road[i];
        wf.update(a,b,c,false);
        wf.update(b,a,c,false);
    }
    auto dist = wf.shortest_path();

    // 逆からクエリ処理
    vector<ll> ans;
    for(ll q=Q-1; q>=0; q--) {
        auto[type,x,y] = query[q];
        if (type == 1) {
            // xを通行止めから解放
            auto[u,v,c] = road[x];
            wf.update_edge(u,v,c,dist);
            wf.update_edge(v,u,c,dist);
        }
        else {
            // x,yの最短距離
            ans.push_back(dist[x][y]);
        }
    }

    // 出力
    reverse(ans.begin(), ans.end());
    for(ll v: ans) {
        if (v == LONG_LONG_MAX) cout << -1 << endl;
        else cout << v << endl;
    }
}


int main() {
    solve();
    return 0;
}