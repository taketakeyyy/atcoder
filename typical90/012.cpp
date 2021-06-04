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
struct UnionFindVerSize {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる

    public:
        UnionFindVerSize(T N=0): sizes(N,1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
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

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (T i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};


void solve() {
    ll H, W; cin >> H >> W;
    vector<vector<ll>> grid(H, vector<ll>(W, 0));
    // ノードの連結は、UnionFindで判定する
    UnionFindVerSize uf = UnionFindVerSize(H*W);

    auto to_node = [W](ll r, ll c) {
        // ノード番号に変換する
        return r*W+c;
    };

    ll Q; cin >> Q;
    for(int q=0; q<Q; q++) {
        ll t; cin >> t;
        if (t==1) {
            ll r, c; cin >> r >> c; r--; c--;
            grid[r][c] = 1;
            if(r-1>=0 && grid[r-1][c]==1) {
                // 上
                uf.unite(to_node(r-1, c), to_node(r, c));
            }
            if (r+1<H && grid[r+1][c]==1) {
                // 下
                uf.unite(to_node(r+1, c), to_node(r, c));
            }
            if (c-1>=0 && grid[r][c-1]==1) {
                // 左
                uf.unite(to_node(r, c-1), to_node(r, c));
            }
            if (c+1<W && grid[r][c+1]==1){
                // 右
                uf.unite(to_node(r, c+1), to_node(r, c));
            }
        }
        else {
            ll ra, ca, rb, cb; cin >> ra >> ca >> rb >> cb;
            ra--; ca--; rb--; cb--;
            if (grid[ra][ca]==1 && grid[rb][cb]==1 && uf.is_same_group(to_node(ra, ca), to_node(rb, cb))) {
                cout << "Yes" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}