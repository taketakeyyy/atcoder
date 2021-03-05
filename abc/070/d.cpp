#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

class Dijkstra {
    /*** ダイクストラ法
     * 重み付きグラフにおける単一始点最短路アルゴリズム
     *  * 使用条件
     *      - 負のコストがないこと
     *      - 有向グラフ、無向グラフともにOK
     *
     *  * 計算量はO(E*log(V))
     *
     *  * ベルマンフォード法より高速なので、負のコストがないならばこちらを使うとよい
     ***/
    private:
        using pll = pair<long long, long long>;
        vector<vector<pll>> graph;  // 隣接リストgraph[u][i]:=頂点uのi個目の隣接辺
        long long e;  // 辺の数
        long long v;  // 頂点の数
    public:
        Dijkstra(long long n) {
            graph.resize(n);
            this->v = n;
            this->e = 0;
        }

        long long get_vertex_num() {
            return this->v;
        }

        long long get_edge_num() {
            return this->e;
        }

        void add(long long u, long long v, long long cost) {
            /* 頂点uから頂点vへのコストはcost */
            this->graph[u].push_back(make_pair(v, cost));
            this->e++;
        }

        vector<long long> shortest_path(long long s) {
            /***
             * Args:
             *   s(long long): 始点s
             * Returns:
             *   dist(vector<long long>): dist[i] := 始点sから頂点iまでの最短コストを格納したリスト。
             *   到達不可の場合、値はLONG_LONG_MAX
             ***/
            /*** [初期化処理] ***/
            vector<long long> dist(this->v, LONG_LONG_MAX);
            dist[s] = 0;
            priority_queue<pll, vector<pll>, greater<pll>> que;  // 小さい順を維持する優先度付きキュー
            que.push(make_pair(0, s));  // 始点の(最短距離の候補, 頂点番号)を追加する（最短距離の候補が小さい順に取り出したいので、firstが最短距離の候補）

            /*** [探索処理] ***/
            while (!que.empty()) {
                /*** [pop処理] ***/
                long long u, d;
                tie(d, u) = que.top();
                que.pop();

                /*** [スキップ判定] ***/
                // キューに格納されている最短経路の候補がdistの距離よりも大きければ、他の経路で最短経路が存在するので、処理をスキップ
                if (dist[u] < d) continue;

                /*** [更新処理] ***/
                for (long long i=0; i<this->graph[u].size(); i++) {
                    long long v, cost;
                    tie(v, cost) = graph[u][i];
                    // 頂点uに隣接する各頂点に対して、頂点uを経由した場合の距離を計算し、今までの距離(dist)よりも小さければ更新する
                    long long ncost = dist[u]+cost; if (dist[u]>0 && cost>0 && ncost<0) ncost = LONG_LONG_MAX;  // オーバーフロー対策
                    if (dist[v] > ncost) {
                        dist[v] = ncost;  // 更新
                        que.push(make_pair(dist[v], v));
                    }
                }
            }
            return dist;
        }
};

void solve() {
    // 頂点xから頂点Kを経由し、頂点yまで移動する際の最短距離を求めたい。
    // (xからKまでの最短距離) + (Kからyまでの最短距離) を求めたい。
    // 頂点Kは固定なので、頂点Kからダイクストラをすれば、dist[x]+dist[y]を出力すれば良い
    // ダイクストラはO(Nlog(N))
    // log(N) = 16.6くらい。ちっさ。
    ll N; cin >> N;
    vector<vector<pair<ll,ll>>>G(N);
    Dijkstra djk = Dijkstra(N);
    for(int i=0; i<N-1; i++) {
        ll a,b,c; cin >> a >> b >> c;
        a--; b--;
        djk.add(a,b,c);
        djk.add(b,a,c);
    }
    ll Q, K; cin >> Q >> K;
    K--;
    vector<long long>dist = djk.shortest_path(K);
    for(int i=0; i<Q; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        cout << dist[x]+dist[y] << endl;
    }
}


int main() {
    solve();
    return 0;
}