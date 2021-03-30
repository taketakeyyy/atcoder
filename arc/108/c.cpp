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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


template <typename T>
struct UnionFindVerDepth {
    private:
        vector<T> depths;   // グループの深さ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
    public:
        map<pair<ll,ll>,ll> edges;    // (u,v)間の辺のラベル
        vector<vector<pair<ll,ll>>> Gs;  // 辺情報(頂点,ラベル番号)
        vector<T> labels;   // 頂点のラベル

        UnionFindVerDepth(T N=0): depths(N,-1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
            this->labels.resize(N);
            this->Gs.resize(N);
        }

        T find_root(T x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(T x, T y, T c) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            T gx = this->find_root(x); T gy = this->find_root(y);
            if (gx == gy) {
                return;
            }

            this->Gs[x].push_back(make_pair(y,c));
            this->Gs[y].push_back(make_pair(x,c));

            // 深い方が浅い方を併合する（木の偏りが減るので）
            if (this->depths[gx] < this->depths[gy]) {
                this->parents[gx] = gy;
            }
            else {
                this->parents[gy] = gx;
                if (this->depths[gx] == this->depths[gy]) this->depths[gx] += 1;
            }
            this->edges[make_pair(min<ll>(x,y), max<ll>(x,y))] = c;
        }

        T get_depth(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->depths[this->find_root(x)];
        }

        bool is_same_group(T x, T y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        T calc_group_num() {
            /* グループ数を計算して返す */
            T ans = 0;
            for (T i=0; i<this->parents.size(); i++) {
                if (i == this->find_root(i)) ans++;
            }
            return ans;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (T i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_depths() {
            /* デバッグ用depthsの中身を出力する */
            for (T i=0; i<this->depths.size(); i++) {
                cout << this->depths[i] << endl;
            }
        }
};



void solve() {
    // 実は、適当な全域木を作り、頂点に整数を書き込んでいけばよい
    // 連結性が重要=>全域木を考える、というのは重要
    // 全域木の構築は、UnionFindを使えばOK
    ll N, M; cin >> N >> M;
    UnionFindVerDepth<ll> uf = UnionFindVerDepth<ll>(N);
    for (int i=0; i<M; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        uf.unite(u, v, c);
    }

    ll g = uf.find_root(0);
    uf.labels[g] = 1;  // なんでもよさげ
    deque<ll> deq;
    deq.push_back(g);
    set<ll> visited;
    while(deq.size()!=0) {
        ll u = deq.front(); deq.pop_front();

        if (visited.count(u)) continue;
         visited.insert(u);

        for (auto [v,c]:uf.Gs[u]) {
            // if (uf.labels[v]!=0) continue;
            if (visited.count(v)) continue;

            if (c==uf.labels[u]) {
                uf.labels[v] = c%N+1;  // cじゃないならなんでもいい
            }
            else {
                uf.labels[v] = c;
            }
            deq.push_back(v);
        }
    }

    // 出力
    for(int i=0; i<N; i++) {
        cout << uf.labels[i] << endl;
    }
}

void solve2() {
    // UnionFindを使わないで全域木を構築する
    // 構築というか、この問題は連結が保障されているので、連結成分は1であることが保障されている
    // 根から順に子を辿っていき、すでに到達済みの頂点はもう辿らないという方針でBFSするだけでよい。
    ll N, M; cin >> N >> M;
    vector<vector<pair<ll,ll>>> G(N);
    for (int i=0; i<M; i++) {
        ll u, v, c; cin >> u >> v >> c;
        u--; v--;
        G[u].push_back(make_pair(v,c));
        G[v].push_back(make_pair(u,c));
    }
    vector<ll> ans(N);
    ans[0] = 1;  // 根は適当に頂点0として、適当にラベルをつける
    deque<ll> deq; deq.push_back(0);
    set<ll> visited;

    while(deq.size()!=0) {
        ll u = deq.front(); deq.pop_front();
        if (visited.count(u)) continue;
        visited.insert(u);

        for(auto [v, c]: G[u]) {
            if (visited.count(v)) continue;
            if (c == ans[u]) {
                ans[v] = c%N+1;
            }
            else {
                ans[v] = c;
            }
            deq.push_back(v);
        }
    }

    // 出力
    for (int i=0; i<N; i++) {
        cout << ans[i] << endl;
    }
}



int main() {
    solve2();
    return 0;
}