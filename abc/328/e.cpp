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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

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

// 半分全列挙
void solve() {
    ll N, M, K; cin >> N >> M >> K;

    vector<tuple<ll,ll,ll>> edges(M);
    for(ll i=0; i<M; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        edges[i] = {u, v, w};
    }

    // edgesの[l,r)の範囲を使ったコストの最小値
    auto genP = [&](ll l, ll r) -> vector<set<ll>>{
        // 使う分の辺だけ抽出する
        vector<tuple<ll,ll,ll>> Es;
        for(ll i=l; i<r; i++) {
            Es.push_back(edges[i]);
        }

        // 半分全列挙
        auto uf = UnionFindVerSize<ll>(N);

        vector<set<ll>> P(1<<N); // P[state] := 使われている頂点がstateの状態のコストの集合
        ll NE = Es.size();
        for(ll bit=0; bit<(1<<NE); bit++) { // どの辺を使うか全探索する
            ll total = 0;
            ll state = 0;
            for(ll d=0; d<NE; d++) {
                if (bit>>d&1) {
                    auto[u, v, c] = Es[d];
                    total += c; total %= K;
                    state |= (1<<u);
                    state |= (1<<v);
                }
            }
            P[state].insert(total);
        }
        return P;
    };
    auto P1 = genP(0, M/2);
    auto P2 = genP(M/2, M);

    ll ans = K-1;
    if ((ll)P1[(1<<N)-1].size() >= 1) {
        auto it = P1[(1<<N)-1].begin();
        chmin(ans, *it);
    }
    if ((ll)P2[(1<<N)-1].size() >= 1) {
        auto it = P2[(1<<N)-1].begin();
        chmin(ans, *it);
    }
    for(ll state1=0; state1<(1<<N); state1++) { // 256
        for(ll state2=0; state2<(1<<N); state2++) { // 256
            if ((state1|state2) != (1<<N)-1) continue;
            // グラフの連結判定をしたい
            // 無理。「使った頂点がN個 = 連結」ではない。無事死亡。

            for(ll k1: P1[state1]) {
                { // K-k1以上の最小の数を足してみる
                    auto it = P2[state2].lower_bound(K-k1);
                    if (it != P2[state2].end()) {
                        chmin(ans, (k1+(*it))%K);
                    }
                }

                // 最も小さいやつを足してみる
                {
                    auto it = P2[state2].begin();
                    if (it != P2[state2].end()) {
                        chmin(ans, (k1+(*it))%K);
                    }
                }
            }
        }
    }
    cout << ans << endl;
}


// 解説AC
// 全域木の辺の数は必ずN-1本！
// 全域木が大前提なので、N-1本の辺を使う場合を全通り試す
// 辺の最大数は、N=8のとき28本
// C(28, 7) = 1184040 全通り試せる
void solve2() {
    ll N, M, K; cin >> N >> M >> K;

    vector<tuple<ll,ll,ll>> edges(M);
    for(ll i=0; i<M; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        edges[i] = {u, v, w};
    }

    // C(M,N-1)通り全て試す
    ll ans = K-1;
    for(ll bit=0; bit<(1<<M); bit++) { // 2^28=2e8回回しているが、いけるらしい
        if (__builtin_popcount(bit) != N-1) continue;

        ll res = 0;
        auto uf = UnionFindVerSize(N);
        for(ll d=0; d<M; d++) {
            if (!(bit>>d&1)) continue;
            auto[u, v, w] = edges[d];
            uf.unite(u,v);
            res += w; res %= K;
        }

        // 全域木になってるか？
        if (uf.get_size(0) != N) continue;
        ans = min(ans, res);
    }
    cout << ans << endl;
}

// solve2でnext_permutationを使う場合。こっちのほうが速度が早い
void solve3() {
    ll N, M, K; cin >> N >> M >> K;

    vector<tuple<ll,ll,ll>> edges(M);
    for(ll i=0; i<M; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        edges[i] = {u, v, w};
    }

    // C(M,N-1)通り全て試す
    vector<ll> A(M, 0); // M本中N-1本選ぶ用の配列
    for(ll i=0; i<N-1; i++) A[i] = 1;
    sort(A.begin(), A.end());
    ll ans = K-1;
    do{
        ll res = 0;
        auto uf = UnionFindVerSize(N);
        for(ll d=0; d<M; d++) {
            if (A[d] == 0) continue;
            auto[u, v, w] = edges[d];
            uf.unite(u,v);
            res += w; res %= K;
        }

        // 全域木になってるか？
        if (uf.get_size(0) != N) continue;
        ans = min(ans, res);
    }while(next_permutation(A.begin(), A.end()));
    cout << ans << endl;
}

int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}