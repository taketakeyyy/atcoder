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
        set<T> cycles;  // グラフがサイクルの場合、その根を保持する
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
            if (gx == gy) {
                // (★1) すでに同じグループに所属しているので、サイクル発生
                this->cycles.insert(gx);
                return;
            }

            // (★2)併合するときに、片方がサイクルだったら、併合後もサイクルになる
            bool flag_cycle = false;
            if (this->is_cycle(gx) || this->is_cycle(gy)) {
                flag_cycle = true;
                this->cycles.erase(gx);  // 消しとく
                this->cycles.erase(gy);  // 消しとく
            }

            // 深い方が浅い方を併合する（木の偏りが減るので）
            ll g;
            if (this->sizes[gx] < this->sizes[gy]) {
                this->parents[gx] = gy;
                this->sizes[gy] += this->sizes[gx];
                g = gy;
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
                g = gx;
            }

            if (flag_cycle) {
                this->cycles.insert(g);  // (★2)併合後もサイクル
            }
        }

        T get_size(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }

        bool is_cycle(T x) {
            T gx = this->find_root(x);
            return (bool)this->cycles.count(gx);
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
    const ll A_MAX = 400000;
    ll N; cin >> N;
    UnionFindVerSize<ll> uf(A_MAX);
    for(int i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        uf.unite(a, b);
    }

    // 各連結成分のグラフにおいて、
    // (1) 連結成分のグラフが木の場合、頂点数-1個光らせることができる。
    // (2) 連結成分のグラフが木でない場合（サイクルの場合）、頂点数個光らせることができる。
    ll ans = 0;
    set<ll> seen;  // 既に見た連結成分のグラフ
    for(int i=0; i<A_MAX; i++) {
        ll gi = uf.find_root(i);
        if (seen.count(gi)) continue;
        seen.insert(gi);

        if (uf.is_cycle(gi)) {
            ans += uf.get_size(gi);
        }
        else {
            ans += uf.get_size(gi)-1;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}