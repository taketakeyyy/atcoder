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

template <typename T>
struct UnionFindVerSize {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる

    public:
        T group_num;  // 連結成分の個数
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

        T calc_group_num() {
            /* グループ数を計算して返す */
            T ans = 0;
            for (T i=0; i<(T)this->parents.size(); i++) {
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

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (T i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};


void solve() {
    ll N, M; cin >> N >> M;

    // i=N-1から繋げていき、連結成分の個数を数える。
    // 最終的な結果は逆
    vector<set<ll>> edge(N);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        edge[a].insert(b);
        edge[b].insert(a);
    }

    // i=N-1から繋げていく
    UnionFindVerSize uf = UnionFindVerSize<ll>(N);
    // cout << uf.calc_group_num() << endl;
    vector<ll> ans(N+1, 0);
    ans[N] = 0;
    for(ll i=N-1; i>=0; i--) {
        for(auto v: edge[i]) {
            if (v < i) continue;
            uf.unite(i, v);
        }

        // ll num = uf.calc_group_num() - i;
        // ans[i] = num;
        ans[i] = uf.group_num - i;
    }

    // 答え出力
    for(ll i=1; i<=N; i++) {
        cout << ans[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}