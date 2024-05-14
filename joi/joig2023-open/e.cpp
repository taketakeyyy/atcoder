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


void solve() {
    ll H, W; cin >> H >> W;
    vector<vector<ll>> A(H, vector<ll>(W, 0LL));
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) cin >> A[i][j];
    }

    // グリッドの中に収まっているか？
    auto is_inside = [&](ll h, ll w) {
        return h>=0 and h<H and w>=0 and w<W;
    };

    // 上左
    const vector<ll> vy = { -1, 0 };
    const vector<ll> vx = { 0, -1 };

    // 左から平面走査する
    auto f = [&](vector<vector<ll>> &A) {
        vector<ll> res(W-1); // res[k] := kに運河を建設したときの、運河より左側の平地の数
        UnionFindVerSize<ll> uf(H*W);

        set<ll> roots; // グループの代表を管理する
        for(ll w=0; w<W-1; w++) {
            for(ll h=0; h<H; h++) {
                ll id = h*W+w;
                roots.insert(uf.find_root(id));
                for(ll vi=0; vi<2; vi++) { // 隣接は上と左だけ見る
                    ll nw = w + vx[vi];
                    ll nh = h + vy[vi];
                    ll nid = nh*W+nw;
                    if (!is_inside(nh, nw)) continue;
                    if (A[h][w]!=A[nh][nw]) continue;
                    roots.erase(uf.find_root(id));
                    roots.erase(uf.find_root(nid));
                    uf.unite(id, nid);
                    roots.insert(uf.find_root(id));
                }
            }
            res[w] = roots.size();
        }

        return res;
    };
    auto left = f(A);

    // 右から左もやる
    for(ll i=0; i<H; i++) reverse(A[i].begin(), A[i].end());
    auto right = f(A);
    reverse(right.begin(), right.end());

    // 答えを探す
    ll ans = INF;
    for(ll w=0; w<W-1; w++) {
        chmin(ans, left[w]+right[w]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}