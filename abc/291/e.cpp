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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };



ll N;
vector<set<ll>> G;
vector<set<ll>> invG;
// 直径がN-1になるか調べる
ll ans_a = 1;
vector<ll> ans;
bool dfs(ll u, ll depth, vector<ll> &visited) {
    if (depth == N-1) {
        ans[u] = ans_a++;
        return true;
    }

    for(ll v: invG[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        bool res = dfs(v, depth+1, visited);
        if (res) {
            ans[u] = ans_a++;
            return true;
        }
        visited[v] = false;
    }
    return false;
}


// 制約より、入力に矛盾しないAが存在するので、閉路ができることはない。
// XからYに有効辺を張り、DAGができて全頂点を辿ることができたらOK
// WA
void solve() {
    ll M; cin >> N >> M;

    vector<ll> X(M), Y(M);
    ans.resize(N);
    G.resize(N);
    invG.resize(N);
    for(ll i=0; i<M; i++) {
        cin >> X[i] >> Y[i];
        X[i]--; Y[i]--;
        G[X[i]].insert(Y[i]);
        invG[Y[i]].insert(X[i]);
    }

    // まず、適当な頂点から初めて、葉を見つける
    ll leaf;
    {
        vector<ll> visited(N, false);
        visited[0] = true;
        deque<ll> deq; deq.push_back(0);
        while(!deq.empty()) {
            ll u = deq.front(); deq.pop_front();
            leaf = u;
            for(ll v: G[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                deq.push_back(v);
            }
        }
    }

    // グラフを木にする
    // {
    //     vector<ll> visited(N, false);
    //     visited[leaf] = true;
    //     deque<ll> deq;
    //     deq.push_back(leaf);
    //     vector<vector<pair<ll,ll>>> erase_cands(N);  // (u,v)の辺を削除すべき
    //     while(!deq.empty()) {
    //         ll u = deq.front();
    //         deq.pop_front();

    //         for(ll v: invG[u]) {
    //             if (visited[v]) {
    //                 for(auto[eu, ev] :erase_cands[v]) {
    //                     invG[eu].erase(ev);
    //                 }
    //                 erase_cands[v].push_back({u,v});
    //                 continue;
    //             }
    //             visited[v] = true;
    //             deq.push_back(v);
    //             erase_cands[v].push_back({u,v});
    //         }
    //     }
    // }

    // 葉からグラフの直径を求めて、直径がN-1にできるなら、一意に定まる
    {
        vector<ll> visited(N, false);
        visited[leaf] = true;
        bool res = dfs(leaf, 0, visited);
        if (res) {
            cout << "Yes" << endl;
            for(ll i=0; i<N; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    // {
    //     vector<ll> visited(N, false);
    //     visited[leaf] = true;
    //     deque<ll> deq;
    //     deq.push_back(leaf);
    //     ll i = N;
    //     while(!deq.empty()) {
    //         ll u = deq.front();
    //         deq.pop_front();
    //         ans[u] = i--;

    //         for(ll v: invG[u]) {
    //             if (visited[v]) continue;
    //             visited[v] = true;
    //             deq.push_back(v);
    //         }
    //     }

    //     if (i == 0) {
    //         cout << "Yes" << endl;
    //         for(ll i=0; i<N; i++) {
    //             cout << ans[i] << " ";
    //         }
    //         cout << endl;
    //     }
    //     else {
    //         cout << "No" << endl;
    //     }
    // }
}


/**トポロジカルソート（DAG）
 * 閉路のない有向グラフ
 * 「どの頂点iについても、行き先の頂点番号が、頂点iよりも大きくなる」という性質を持つ
 *
 * Args:
 *  N(T): 頂点数（整数）
 *
 * Notes:
 *  キューにdequeを使っている
 *  * 計算量
 *    - dequeを使うと、O(|E|+|V|)
 *
 * Usage:
 *   // DAGの宣言
 *   DAG dag = DAG<long long>(N);
 *
 *   // 辺を追加する
 *   // 1 → 0
 *   //   ↘
 *   // 2 → 3
 *   dag.add_edge(1, 0);
 *   dag.add_edge(2, 3);
 *   dag.add_edge(1, 3);
 *
 *   // DAGの構築
 *   dag.build();
 *
 *   // DAGの構築成功なら、DAGを出力
 *   if (dag.is_build_success()) {
 *       // DAGの出力（頂点をトポロジカル順序で出力）
 *       for(long long i=0; i<N; i++) {
 *           cout << dag.dag[i] << endl;
 *       }
 *   }
 *
 **/
template<typename T>
class DAG {
    private:
        vector<T> in_degrees;  // in_degrees[i] := ノードiの入次数
        vector<vector<T>> G;  // G[i] := ノードiに隣接しているノードの集合（配列）

    public:
        T V;  // 頂点数
        T E = 0;  // 辺の数
        vector<T> dag;  // トポロジカル順序で並んだ要素の配列

        DAG(T N) {
            this->V = N;
            this->in_degrees.assign(N, 0);
            this->G.resize(N);
        }

        /*** 頂点uから頂点vへの辺を追加する
         ***/
        void add_edge(T u, T v) {
            this->G[u].emplace_back(v);
            this->in_degrees[v]++;
            this->E++;
        }

        /*** DAGを構築する
         ***/
        void build() {
            deque<T> que;

            // まず、入次数0の頂点をキューに追加する
            for(T i=0; i<this->V; i++) {
                if (in_degrees[i]==0) que.push_back(i);
            }

            // 「キューに入っている頂点を削除する」処理を繰り返す
            while(!que.empty()) {
                T u = que.front(); que.pop_front();

                // 頂点uを削除するので、頂点uに隣接している頂点の入次数を減らす
                for(auto v: G[u]) {
                    this->in_degrees[v]--;
                    if (this->in_degrees[v] == 0) que.push_back(v);  // 入次数が0になった頂点は、キューに追加する
                }

                this->dag.emplace_back(u);
            }
        }

        /*** DAGの構築に成功したか？
         * 閉路があると、失敗する
         ***/
        bool is_build_success() {
            return (T)this->dag.size()==this->V;
        }
};

// 解説AC
// xからyに辺を張って、DAGを作る。
// 制約より、矛盾のないAが存在するので、閉路が発生することはない。
// 一意なDAGになればいい。一意なDAGとは、トポロジカル順序が一意ということ。
// DAG構築過程で、入次数0の頂点が一意であることが必要十分条件。
void solve2() {
    ll N, M; cin >> N >> M;

    // XからYに辺を張り、グラフを作る
    vector<set<ll>> G(N);
    vector<ll> indeg(N, 0);  // 各頂点の入次数
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        if (G[x].count(y)) continue; // 重複辺注意
        G[x].insert(y);
        indeg[y]++;
    }

    // 一意なDAGを構築する
    vector<ll> dag;
    {
        // 入次数0の頂点をキューに入れる
        deque<ll> deq;
        for(ll i=0; i<N; i++) {
            if (indeg[i] == 0) deq.push_back(i);
        }

        while(!deq.empty()) {
            // キュー内のサイズが2以上なら、一意なDAGになれない
            if ((ll)deq.size() >= 2) {
                cout << "No" << endl;
                return;
            }

            ll u = deq.front(); deq.pop_front();
            dag.push_back(u);
            for(ll v: G[u]) {
                // 頂点uに隣接している頂点の入次数を減らす
                indeg[v]--;
                if (indeg[v] == 0) deq.push_back(v);
            }
        }
    }

    // 一意なDAGができていたら出力する
    vector<ll> ans(N);
    ll a = 1;
    for(ll i=0; i<N; i++) {
        ans[dag[i]] = a++;
    }
    cout << "Yes" << endl;
    for(ll i=0; i<N; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

// 解説AC
// トポロジカル順序が一意であることは、G の最長パスの長さが N−1 であることとも同値であるため、これにより判定することもできます
// DFSのパス長を求める
void solve3() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        if (G[x].count(y)) continue;
        G[x].insert(y);
    }

    // 各頂点の葉からの距離をDFSで求める
    vector<ll> length(N, -1); // 葉からの距離
    auto dfs = [&](auto dfs, ll u) -> ll {
        if (length[u] != -1) return length[u];
        length[u] = 0;
        for(ll v: G[u]) {
            length[u] = max(length[u], dfs(dfs,v)+1);
        }
        return length[u];
    };

    // 最長パスを求める
    ll longest = 0;
    for(ll u=0; u<N; u++) {
        longest = max(longest, dfs(dfs,u));
    }

    // 出力
    if (longest == N-1) {
        cout << "Yes" << endl;
        for(ll x: length) {
            cout << N-x << " ";
        }
        cout << endl;
    }
    else {
        cout << "No" << endl;
    }
}


// 解説AC
// トポロジカル順序が一意であることは、G の最長パスの長さが N−1 であることとも同値であるため、これにより判定することもできます
// 最長パスの長さをDPで求める
void solve4() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    vector<set<ll>> invG(N);
    vector<ll> indeg(N);  // 入次数
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        if (G[x].count(y)) continue;
        G[x].insert(y);
        invG[y].insert(x);
        indeg[y]++;
    }

    // DAGをまず作る
    vector<ll> dag;
    {
        deque<ll> deq;
        for(ll i=0; i<N; i++) {
            if (indeg[i] == 0) deq.push_back(i);
        }

        while(!deq.empty()) {
            ll u = deq.front(); deq.pop_front();
            dag.push_back(u);
            for(ll v: G[u]) {
                indeg[v]--;
                if (indeg[v] == 0) deq.push_back(v);
            }
        }
    }

    // DAGを使ってDPで距離を求める
    vector<ll> dp(N, 0); // dp[u] := 頂点uの、DAGの根からの最長距離
    {
        for(ll i=0; i<N; i++) {
            ll u = dag[i];
            for(ll v: G[u]) {
                dp[v] = max(dp[v], dp[u]+1);
            }
        }
    }

    // 最長パスの長さがN-1なら、一意なトポロジカル順序を持つDAGである
    ll longest = 0;
    for(ll i=0; i<N; i++) longest = max(longest, dp[i]);
    if (longest == N-1) {
        cout << "Yes" << endl;
        for(ll i=0; i<N; i++) {
            cout << dp[i]+1 << " ";
        }
        cout << endl;
    }
    else {
        cout << "No" << endl;
    }
}




int main() {
    // solve();
    // solve2();
    // solve3();
    solve4();
    return 0;
}