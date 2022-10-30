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

// (1) メルセンヌ・ツイスター法による疑似乱数生成器を、ハードウェア乱数をシードにして初期化
std::random_device seed_gen;
std::mt19937 engine(seed_gen());

const ll N = 10;  // 10x10の箱
vector<vector<ll>> grid(10, vector<ll>(10, 0));  // キャンディーが入る正方形の箱
vector<ll> f(N*N);  // キャンディーの種類

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

/**
 * @brief gridの中に入っているか
 *
 */
bool is_inside(ll h, ll w) {
    return (h>=0 && h<N && w>=0 && w<N);
}

/**
 * @brief 与えられたキャンディー座標pを、gridの座標に変換する
 *
 * @param p
 * @return pair<ll,ll>
 */
pair<ll,ll> put_candy(ll p) {
    ll cnt = 0;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (grid[i][j] == 0) {
                if (cnt == p) return {i, j};
                cnt++;
            }
        }
    }
    return {-1, -1};  // ダミー
}

/**
 * @brief 前方に傾ける（↑）
 *
 */
void move_F(vector<vector<ll>> &grid) {
    for(ll h=0; h<N; h++) {
        for(ll w=0; w<N; w++) {
            if (grid[h][w] == 0) continue;

            // できるだけ上に移動させる
            ll th=h;
            for(ll nh=h-1; nh>=0; nh--) {
                if (grid[nh][w] != 0) break;
                grid[nh][w] = grid[th][w];
                grid[th][w] = 0;
                th = nh;
            }
        }
    }
}

/**
 * @brief 後方に傾ける（↓）
 *
 */
void move_B(vector<vector<ll>> &grid) {
    for(ll h=N-1; h>=0; h--) {
        for(ll w=0; w<N; w++) {
            if (grid[h][w] == 0) continue;

            // できるだけ下に移動させる
            ll th=h;
            for(ll nh=h+1; nh<N; nh++) {
                if (grid[nh][w] != 0) break;
                grid[nh][w] = grid[th][w];
                grid[th][w] = 0;
                th = nh;
            }
        }
    }
}

/**
 * @brief 右方向に傾ける（→）
 *
 */
void move_R(vector<vector<ll>> &grid) {
    for(ll w=N-1; w>=0; w--) {
        for(ll h=0; h<N; h++) {
            if (grid[h][w] == 0) continue;

            // できるだけ右に移動させる
            ll tw=w;
            for(ll nw=w+1; nw<N; nw++) {
                if (grid[h][nw] != 0) continue;
                grid[h][nw] = grid[h][tw];
                grid[h][tw] = 0;
                tw = nw;
            }
        }
    }
}

/**
 * @brief 左方向に傾ける（←）
 *
 */
void move_L(vector<vector<ll>> &grid) {
    for(ll w=0; w<N; w++) {
        for(ll h=0; h<N; h++) {
            if (grid[h][w] == 0) continue;

            // できるだけ左に移動させる
            ll tw=w;
            for(ll nw=w-1; nw>=0; nw--) {
                if (grid[h][nw] != 0) continue;
                grid[h][nw] = grid[h][tw];
                grid[h][tw] = 0;
                tw = nw;
            }
        }
    }
}

/**
 * @brief 評価関数 (O(N^2))
 *
 * @return double
 */
double evaluate_score(vector<vector<ll>> const &grid) {
    map<ll,ll> d;

    UnionFindVerSize<ll> uf(N*N);
    for(ll h=0; h<N; h++) {
        for(ll w=0; w<N; w++) {
            if (grid[h][w] == 0) continue;

            d[grid[h][w]]++;
            ll id = h*10 + w;

            // 上下左右に連結できるか見る
            for(ll vi=0; vi<4; vi++) {
                ll nh = h + vy[vi];
                ll nw = w + vx[vi];
                ll nid = nh*10 + nw;
                if (!is_inside(nh, nw)) continue;
                if (grid[h][w] != grid[nh][nw]) continue;
                uf.unite(id, nid);
            }
        }
    }

    // 連結成分の大きさを調べる
    double bunshi = 0;
    set<ll> done;
    for(ll h=0; h<N; h++) {
        for(ll w=0; w<N; w++) {
            ll id = h*10 + w;
            ll root = uf.find_root(id);
            if (done.count(root)) continue;
            done.insert(root);
            ll n = uf.get_size(root);
            bunshi += (n*n);
        }
    }

    // 分母を算出
    double bunbo = 0.00000001;  // ゼロ除算回避
    for(ll i=1; i<=3; i++) {
        bunbo += d[i]*d[i];
    }

    return 1e6 * (bunshi) / (bunbo);
}

/**
 * @brief いちごなら右に、スイカなら左に、パンプキンなら手前
 *
 * @return vector<char>
 */
void baka_solver() {
    for(ll t=0; t<N*N; t++) {
        ll p; cin >> p; p--;
        auto[x, y] = put_candy(p);
        grid[x][y] = f[t];  // キャンディーを置く

        char dir;
        if (f[t] == 1) dir = 'R';
        else if (f[t] == 2) dir = 'L';
        else dir = 'B';

        printf("%c\n", dir);
    }
}

/**
 * @brief 出力
 *
 * @param ans
 */
void output(vector<char> const &ans) {
    for(ll i=0; i<(ll)ans.size(); i++) {
        printf("%c\n", ans[i]);
        flush(cout);
    }
}

void solve() {
    // キャンディーの種類
    for(ll i=0; i<N*N; i++) {
        cin >> f[i];
    }

    baka_solver();
}


int main() {
    solve();
    return 0;
}