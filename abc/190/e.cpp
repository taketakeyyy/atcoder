#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


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
        using pii = pair<int, int>;
        vector<vector<pii>> graph;  // 隣接リストgraph[u][i]:=頂点uのi個目の隣接辺
        int e;  // 辺の数
        int v;  // 頂点の数
    public:
        Dijkstra(int n) {
            graph.resize(n);
            this->v = n;
            this->e = 0;
        }

        int get_vertex_num() {
            return this->v;
        }

        int get_edge_num() {
            return this->e;
        }

        void add(int u, int v, int cost) {
            /* 頂点uから頂点vへのコストはcost */
            this->graph[u].emplace_back(make_pair(v, cost));
            this->e++;
        }

        vector<int> shortest_path(int s) {
            /***
             * Args:
             *   s(int): 始点s
             * Returns:
             *   dist(vector<int>): dist[i] := 始点sから頂点iまでの最短コストを格納したリスト。
             *   到達不可の場合、値はINT_MAX
             ***/
            /*** [初期化処理] ***/
            vector<int> dist(this->v, INT_MAX);
            dist[s] = 0;
            priority_queue<pii, vector<pii>, greater<pii>> que;
            que.push(make_pair(s, 0));  // 始点の(頂点番号, 最短距離の候補)を追加する

            /*** [探索処理] ***/
            while (!que.empty()) {
                /*** [pop処理] ***/
                int u, d;
                tie(u, d) = que.top();
                que.pop();

                /*** [スキップ判定] ***/
                // キューに格納されている最短経路の候補がdistの距離よりも大きければ、他の経路で最短経路が存在するので、処理をスキップ
                if (dist[u] < d) continue;

                /*** [更新処理] ***/
                for (int i=0; i<this->graph[u].size(); i++) {
                    int v, cost;
                    tie(v, cost) = graph[u][i];
                    // 頂点uに隣接する各頂点に対して、頂点uを経由した場合の距離を計算し、今までの距離(dist)よりも小さければ更新する
                    int ncost = dist[u]+cost; if (dist[u]>0 && cost>0 && ncost<0) ncost = INT_MAX;  // オーバーフロー対策
                    if (dist[v] > ncost) {
                        dist[v] = ncost;  // 更新
                        que.push(make_pair(v, dist[v]));
                    }
                }
            }
            return dist;
        }
};


void solve(){
    /* TLE */
    int N, M; cin >> N >> M;
    Dijkstra djk = Dijkstra(N);
    for (int i=0; i<M; i++) {
        int A, B; cin >> A >> B; A--; B--;
        djk.add(A, B, 1); djk.add(B, A, 1);
    }

    int K; cin >> K;
    vector<int> Cs(K);
    for (int i=0; i<K; i++) {
        int C; cin >> C; C--;
        Cs[i] = C;
    }

    vector<vector<int>> dists;
    for (int i=0; i<K; i++) {
        dists.emplace_back(djk.shortest_path(Cs[i]));  // 始点cからの最短距離を求める
    }

    // for (int i=0; i<K; i++) {
    //     cout << "FROM:" << Cs[i] << endl;
    //     for (int j=0; j<K; j++) {
    //         cout << Cs[j] << ":" << dists[i][Cs[j]] << endl;
    //     }
    // }

    // bitDP[S][i] := 既に訪れた重要宝石集合Sにおいて、現在の重要宝石がiのときの、最短距離
    vector<vector<int>> dp(1<<K, vector<int>(K, INT_MAX));
    for (int i=0; i<K; i++) {
        dp[0][i] = 0;
    }
    for (int i=0; i<K; i++) {
        for (int j=0; j<K; j++) {
            dp[(1<<i)|(1<<j)][j] = dists[i][Cs[j]];
        }
    }
    for (int S=1; S<(1<<K); S++) {
        for (int i=0; i<K; i++) {  // 現在の宝石i
            if (~S>>i&1) continue;  // iはまだ訪れていない
            for (int j=0; j<K; j++) {  // 次に行く宝石j
                if (S>>j&1) continue;  // jは既に訪れている
                int new_cost = dp[S][i]+dists[i][Cs[j]];
                if (new_cost<0) new_cost = INT_MAX;  // オーバーフロー対策
                dp[S|1<<j][j] = min(dp[S|1<<j][j], new_cost);
            }
        }
    }

    // 答え
    int ans = INT_MAX;
    for (int i=0; i<K; i++) {
        ans = min(ans, dp[pow(2,K)-1][i]);
    }
    if (ans == INT_MAX) {
        cout << -1 << endl;
    }
    else {
        cout << ans+1 << endl;
    }
}


vector<int> BFS(int n, vector<vector<int>>& paths, int& N) {
    // BFSで宝石nから各宝石までの距離を求める
    vector<int> dist(N, INT_MAX); dist[n] = 0;
    set<int> visited; visited.insert(n);
    deque<int> que; que.push_back(n);
    while(!que.empty()) {
        int now = que.front();
        que.pop_front();

        for (int nx: paths[now]) {
            if (visited.count(nx)) continue;
            visited.insert(nx);
            dist[nx] = min(dist[nx], dist[now]+1);
            que.push_back(nx);
        }
    }
    return dist;
}

void solve2(){
    int N, M; cin >> N >> M;
    vector<vector<int>> paths(N);
    for (int i=0; i<M; i++) {
        int A, B; cin >> A >> B; A--; B--;
        paths[A].push_back(B);
        paths[B].push_back(A);
    }

    int K; cin >> K;
    vector<int> Cs(K);
    for (int i=0; i<K; i++) {
        int C; cin >> C; C--;
        Cs[i] = C;
    }

    vector<vector<int>> dists;
    for (int i=0; i<K; i++) {
        dists.emplace_back(BFS(Cs[i], paths, N));  // 始点cからの最短距離を求める
    }

    // for (int i=0; i<K; i++) {
    //     cout << "FROM:" << Cs[i] << endl;
    //     for (int j=0; j<K; j++) {
    //         cout << Cs[j] << ":" << dists[i][Cs[j]] << endl;
    //     }
    // }

    // bitDP[S][i] := 既に訪れた重要宝石集合Sにおいて、現在の重要宝石がiのときの、最短距離
    vector<vector<int>> dp(1<<K, vector<int>(K, INT_MAX));
    for (int i=0; i<K; i++) {
        dp[0][i] = 0;
    }
    for (int i=0; i<K; i++) {
        for (int j=0; j<K; j++) {
            dp[(1<<i)|(1<<j)][j] = dists[i][Cs[j]];
        }
    }
    for (int S=1; S<(1<<K); S++) {
        for (int i=0; i<K; i++) {  // 現在の宝石i
            if (~S>>i&1) continue;  // iはまだ訪れていない
            for (int j=0; j<K; j++) {  // 次に行く宝石j
                if (S>>j&1) continue;  // jは既に訪れている
                int new_cost = dp[S][i]+dists[i][Cs[j]];
                if (new_cost<0) new_cost = INT_MAX;  // オーバーフロー対策
                dp[S|1<<j][j] = min(dp[S|1<<j][j], new_cost);
            }
        }
    }

    // 答え
    int ans = INT_MAX;
    for (int i=0; i<K; i++) {
        ans = min(ans, dp[pow(2,K)-1][i]);
    }
    if (ans == INT_MAX) {
        cout << -1 << endl;
    }
    else {
        cout << ans+1 << endl;
    }
}


int main(int argc, char const *argv[]){
    solve2();
    return 0;
}