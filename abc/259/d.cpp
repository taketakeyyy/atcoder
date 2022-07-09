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

ll distance(ll x1, ll y1, ll x2, ll y2) {
    // 距離の2乗を返す
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void solve() {
    ll N; cin >> N;
    ll sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;
    vector<ll> X(N), Y(N), R(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i] >> R[i];
    }

    UnionFindVerSize<ll> uf(N+2);
    for(ll i=0; i<N; i++) {
        ll x1 = X[i], y1 = Y[i];
        ll r1 = R[i];
        for(ll j=i+1; j<N; j++) {
            ll x2 = X[j], y2 = Y[j];
            ll r2 = R[j];
            ll d = distance(x1, y1, x2, y2);
            ll rmax = max(r1, r2);
            ll rmin = min(r1, r2);
            if (d < (rmax-rmin)*(rmax-rmin)) {
                continue;
            }
            if (d <= (r1+r2)*(r1+r2)) {
                uf.unite(i, j);
            }
        }
    }

    for(ll i=0; i<N; i++) {
        ll x1 = X[i], y1 = Y[i];
        ll r1 = R[i];

        ll ds = distance(sx, sy, x1, y1);
        if (ds <= r1*r1) {
            uf.unite(i, N);
            break;
        }
    }
    for(ll i=0; i<N; i++) {
        ll x1 = X[i], y1 = Y[i];
        ll r1 = R[i];

        ll dt = distance(tx, ty, x1, y1);
        if (dt <= r1*r1) {
            uf.unite(i, N+1);
            break;
        }
    }

    if (uf.is_same_group(N, N+1)) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}