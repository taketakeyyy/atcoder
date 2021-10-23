#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
         * Notes:
         *  キューにpriority_queを使っている
         *  キューはdequeでもOK
         *  priority_queを使うとDAGの出力が辞書順になる（できるだけ昇順になる）
         *  * 計算量
         *    - dequeを使うと、O(|E|+|V|)
         *    - priority_queを使うと、O(|E| log|V| +|V| log|V|)
         *      - push と pop に log|V| かかる
         ***/
        void build() {
            priority_queue<T, vector<T>, greater<T>> que;  // できるだけ昇順にしたい

            // まず、入次数0の頂点をキューに追加する
            for(T i=0; i<this->V; i++) {
                if (in_degrees[i]==0) que.push(i);
            }

            // 「キューに入っている頂点を削除する」処理を繰り返す
            while(!que.empty()) {
                // T u = que.front(); que.pop_front();
                T u = que.top(); que.pop();

                // 頂点uを削除するので、頂点uに隣接している頂点の入次数を減らす
                for(auto v: G[u]) {
                    this->in_degrees[v]--;
                    // if (this->in_degrees[v] == 0) que.push_back(v);  // 入次数が0になった頂点は、キューに追加する
                    if (this->in_degrees[v] == 0) que.push(v);  // 入次数が0になった頂点は、キューに追加する
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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(M);
    vector<ll> B(M);
    for(int i=0; i<M; i++) {
        cin >> A[i] >> B[i];
        A[i]--; B[i]--;
    }

    // DAG
    // 閉路できたら-1
    DAG dag = DAG(N);
    for(ll i=0; i<M; i++) {
        dag.add_edge(A[i], B[i]);
    }
    dag.build();

    if (dag.is_build_success()) {
        for(ll i=0; i<N; i++) {
            cout << dag.dag[i]+1 << " ";
        }
        cout << endl;
    }
    else {
        cout << -1 << endl;
    }
}


int main() {
    solve();
    return 0;
}