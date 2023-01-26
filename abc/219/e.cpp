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
            for (T i=0; i<(T)this->parents.size(); i++) {
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

// 2^16 ≒ 6e4
// 各A[i][j]を使うか使わないかを全探索する。
// ・使うと決めたA[i][j]の隣接マスも使われていないといけない（堀で囲まれている条件）
// ・すべての村が、使うマスの中に存在していないといけない
void solve() {
    vector A(4, vector<ll>(4, 0));
    ll village_num = 0;  // 村の数
    for(ll i=0; i<4; i++) {
        for(ll j=0; j<4; j++) {
            cin >> A[i][j];
            if (A[i][j] == 1) village_num++;
        }
    }

    // (h,w)はマスの中に入っているか？を返す
    auto is_inside = [&](ll h, ll w) -> bool {
        return (h>=0 && h<4 && w>=0 && w<4);
    };

    // bit全探索
    ll ans = 0;
    for(ll bit=0; bit<(1<<16); bit++) {
        ll v_num = 0;  // 村の数
        vector B(4, vector<ll>(4, 0));  // 使うと決めたマス
        ll use_num = 0;  // 使うと決めたマスの個数
        ll sh, sw;  // 連結性を見るときの開始地点
        for(ll d=0; d<16; d++) {
            if (bit>>d&1) {
                ll h = d/4;
                ll w = d%4;
                sh=h; sw=w;
                B[h][w] = 1;
                use_num++;
                if (A[h][w]==1) v_num++;
            }
        }

        // すべての村を含んでいるか？
        if (v_num != village_num) continue;

        // 使うと決めたマスはすべて連結しているか？
        UnionFindVerSize<ll> uf(4*4);
        for(ll h=0; h<4; h++) {
            for(ll w=0; w<4; w++) {
                if (B[h][w] == 0) continue;

                for(ll vi=0; vi<4; vi++) {
                    ll nh = h + vy[vi];
                    ll nw = w + vx[vi];
                    if (!is_inside(nh,nw)) continue;
                    if (B[nh][nw] == 0) continue;
                    uf.unite(h*4+w, nh*4+nw);
                }
            }
        }
        bool is_all_connected = true;
        for(ll h=0; h<4; h++) {
            for(ll w=0; w<4; w++) {
                if (B[h][w] == 0) continue;
                if (uf.is_same_group(sh*4+sw, h*4+w)) continue;
                is_all_connected = false;
            }
        }
        if (!is_all_connected) continue;

        // 自己交差を除外する
        bool is_self_cross = false;
        for(ll h=0; h<3; h++) {
            for(ll w=0; w<3; w++) {
                if (B[h][w]==1 && B[h][w+1]==0 && B[h+1][w]==0 && B[h+1][w+1]==1) is_self_cross = true;
                if (B[h][w]==0 && B[h][w+1]==1 && B[h+1][w]==1 && B[h+1][w+1]==0) is_self_cross = true;
            }
        }
        if (is_self_cross) continue;

        // 多角形になっていないものを除外する
        bool is_polygon = true;
        for(ll i=0; i<2; i++) {
            for(ll j=0; j<2; j++) {
                // 111
                // 101
                // 111
                if (B[i][j]==1 && B[i][j+1]==1 && B[i][j+2]==1 &&
                     B[i+1][j]==1 && B[i+1][j+1]==0 && B[i+1][j+2]==1 &&
                     B[i+2][j]==1 && B[i+2][j+1]==1 && B[i+2][j+2]==1) {
                        is_polygon = false;
                }
            }
        }
        if (!is_polygon) continue;
        {
            // 111
            // 101
            // 101
            // 111
            bool is_polygon = true;
            for(ll j=0; j<2; j++) {
                if (B[0][j]==1 && B[0][j+1]==1 && B[0][j+2]==1 &&
                    B[1][j]==1 && B[1][j+1]==0 && B[1][j+2]==1 &&
                    B[2][j]==1 && B[2][j+1]==0 && B[2][j+2]==1 &&
                    B[3][j]==1 && B[3][j+1]==1 && B[3][j+2]==1
                ) is_polygon = false;
            }
            if (!is_polygon) continue;
        }
        {
            // 1111
            // 1001
            // 1111
            bool is_polygon = true;
            for(ll i=0; i<2; i++) {
                if (B[i][0]==1 && B[i][1]==1 && B[i][2]==1 && B[i][3]==1 &&
                    B[i+1][0]==1 && B[i+1][1]==0 && B[i+1][2]==0 && B[i][3]==1 &&
                    B[i+2][0]==1 && B[i+2][1]==1 && B[i+2][2]==1 && B[i+2][3]==1
                ) is_polygon = false;
            }
            if (!is_polygon) continue;
        }
        {
            // 1111
            // 1001
            // 1011
            // 1111
            // ...めんどくさい！
        }

        // デバッグ出力
        cout << endl;
        for(ll i=0; i<4; i++) {
            for(ll j=0; j<4; j++) {
                cout << B[i][j] << " ";
            }
            cout << endl;
        }
        ans++;
    }
    cout << ans << endl;
}

// 2^16 ≒ 6e4
// 各A[i][j]のマスを使うか使わないかを全探索する。
// ・使うと決めたマスの隣接マスも使われていないといけない（堀で囲まれている条件）
// ・すべての村が、使うマスの中に存在していないといけない
void solve2() {
    vector A(4, vector<ll>(4, 0));
    ll village_num = 0;  // 村の数
    for(ll i=0; i<4; i++) {
        for(ll j=0; j<4; j++) {
            cin >> A[i][j];
            if (A[i][j] == 1) village_num++;
        }
    }

    // (h,w)はマスの中に入っているか？を返す
    auto is_inside = [](ll h, ll w) -> bool {
        return (h>=0 && h<6 && w>=0 && w<6);
    };

    // bit全探索
    ll ans = 0;
    for(ll bit=0; bit<(1<<16); bit++) {
        ll v_num = 0;  // 村の数
        // B[i][j] := 周りに1マス増やした6x6の領域で、使うと決めたマスを1にする
        vector B(6, vector<ll>(6, 0));
        for(ll d=0; d<16; d++) {
            if (bit>>d&1) {
                ll h = d/4;
                ll w = d%4;
                B[h+1][w+1] = 1;
                if (A[h][w]==1) v_num++;
            }
        }

        // すべての村を含んでいるか？
        if (v_num != village_num) continue;

        // 使うと決めたマス同士はすべて連結していて、
        // 使わないと決めたマス同士はすべて連結しているか？
        // 正しく堀を作れているなら、連結成分が2になる。
        UnionFindVerSize<ll> uf(6*6);
        for(ll h=0; h<6; h++) {
            for(ll w=0; w<6; w++) {
                if (B[h][w] == 0) {
                    for(ll vi=0; vi<4; vi++) {
                        ll nh = h + vy[vi];
                        ll nw = w + vx[vi];
                        if (!is_inside(nh,nw)) continue;
                        if (B[nh][nw] != 0) continue;
                        uf.unite(h*6+w, nh*6+nw);
                    }
                }
                else {
                    for(ll vi=0; vi<4; vi++) {
                        ll nh = h + vy[vi];
                        ll nw = w + vx[vi];
                        if (!is_inside(nh,nw)) continue;
                        if (B[nh][nw] != 1) continue;
                        uf.unite(h*6+w, nh*6+nw);
                    }
                }
            }
        }
        if (uf.get_group_num() != 2) continue;
        ans++;
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}