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

void solve() {
    ll N; cin >> N;
    vector<tuple<ll,ll,ll>> P(N);//(x,y,街番号)
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        P[i] = {x,y,i};
    }

    UnionFindVerSize<ll> uf(N);

    // 平面走査して、「x,y座標がともに小さい街」を探してグループ化する
    auto f = [&](vector<tuple<ll,ll,ll>> P) {
        sort(P.begin(), P.end());

        // 平面走査
        set<pair<ll,ll>> st; // 各グループの(最小y座標, その頂点番号)の集合
        {
            auto[x0, y0, idx0] = P[0];
            st.insert({y0, idx0});
        }
        for(ll i=1; i<N; i++) {
            auto[x, y, idx] = P[i];
            auto it = st.begin();

            if (st.empty() || it->first > y) {
                // グループが一つもない、または今回のy座標が最小のy座標より小さいなら、新しいグループを作る
                st.insert({y, idx});
                continue;
            }

            // 最も小さいy座標のグループと、ひとまず併合する
            uf.unite(it->second, idx);
            it++;

            // 他のグループとの処理
            for(; it!=st.end();) {
                if (it->first < y) {
                    // このグループと併合し、このグループを集合から削除する
                    uf.unite(it->second, idx);
                    it = st.erase(it);
                }
                else {
                    break;
                }
            }
        }
    };
    f(P);

    // 答え
    for(ll i=0; i<N; i++) {
        cout << uf.get_size(i) << endl;
    }
}


int main() {
    solve();
    return 0;
}