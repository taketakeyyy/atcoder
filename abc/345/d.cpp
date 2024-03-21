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

// これ、DFS部分が3^Nじゃなくて、(H*W+1)^NなのでTLEする
void solve_TLE() {
    ll N, H, W; cin >> N >> H >> W;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    // マス(h,w)に(a,b)のタイルが使えるか探索
    auto f = [&](ll &h, ll &w, ll &a, ll &b) {
        return (h+a<=H and w+b<=W);

    };

    // マス(h,w)にタイル(a,b)を敷く
    auto fill_tile = [&](ll &h, ll &w, ll &a, ll &b, vector<vector<ll>> &used) {

        // imos法
        used[h][w] += 1;
        used[h+a][w+b] += 1;
        used[h+a][w] -= 1;
        used[h][w+b] -= 1;
    };
    // マス(h,w)にタイル(a,b)を取り除く
    auto unfill_tile = [&](ll &h, ll &w, ll &a, ll &b, vector<vector<ll>> &used) {

        // imos法
        used[h][w] -= 1;
        used[h+a][w+b] -= 1;
        used[h+a][w] += 1;
        used[h][w+b] += 1;
    };

    // 完成？
    auto is_complete = [&](vector<vector<ll>> &used) {
        auto imos = used;
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                imos[h][w+1] += imos[h][w];
            }
        }
        for(ll w=0; w<W; w++) {
            for(ll h=0; h<H; h++) {
                imos[h+1][w] += imos[h][w];
            }
        }
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                if (imos[h][w]==1) continue;
                return false;
            }
        }
        return true;
    };

    // 以下のDFSは、(1パターン + H*Wパターン + H*Wパターン)のN乗になるので、TLEする
    auto dfs = [&](auto dfs, ll tile_i, vector<vector<ll>> &used) {
        // 終了条件
        if (tile_i == N) {
            bool is_ok = is_complete(used);
            return is_ok;
        }

        // タイルを使わない場合の探索(1パターン)
        auto res1 = dfs(dfs, tile_i+1, used);
        if (res1) return true;

        // タイルを普通に使う場合の探索(H*Wパターン)
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                bool can_use = f(h, w, A[tile_i], B[tile_i]);
                if (can_use) {
                    fill_tile(h, w, A[tile_i], B[tile_i], used);
                    bool res2 = dfs(dfs, tile_i+1, used);
                    if (res2) return true;
                    unfill_tile(h, w, A[tile_i], B[tile_i], used);
                }
            }
        }

        // タイルを回転して使う場合の探索(H*Wパターン)
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                bool can_use = f(h, w, B[tile_i], A[tile_i]);
                if (can_use) {
                    fill_tile(h, w, B[tile_i], A[tile_i], used);
                    bool res3 = dfs(dfs, tile_i+1, used);
                    if (res3) return true;
                    unfill_tile(h, w, B[tile_i], A[tile_i], used);
                }
            }
        }

        return false;
    };

    vector used(H+1, vector(W+1, 0LL));
    bool ans = dfs(dfs, 0, used);
    if (ans) cout << "Yes" << endl;
    else cout << "No" << endl;
}


// 解説AC
// O(N! * 3^N * HW)
void solve() {
    ll N, H, W; cin >> N >> H >> W;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    auto is_inside = [&](ll h, ll w) {
        return (h>=0 and h<H and w>=0 and w<W);
    };

    // マス(h,w)に(a,b)のタイルが使えるか探索
    // O(HW)
    auto f = [&](ll &h, ll &w, ll &a, ll &b, vector<vector<bool>> &used) {
        for(ll nh=h; nh<h+a; nh++) {
            for(ll nw=w; nw<w+b; nw++) {
                if (!is_inside(nh, nw)) return false;
                if (used[nh][nw]) return false;
            }
        }
        return true;
    };

    // マス(h,w)にタイル(a,b)を敷く
    // O(HW)
    auto fill_tile = [&](ll &h, ll &w, ll &a, ll &b, vector<vector<bool>> &used) {
        for(ll nh=h; nh<h+a; nh++) {
            for(ll nw=w; nw<w+b; nw++) {
                used[nh][nw] = true;
            }
        }
    };
    // マス(h,w)にタイル(a,b)を取り除く
    // O(HW)
    auto unfill_tile = [&](ll &h, ll &w, ll &a, ll &b, vector<vector<bool>> &used) {
        for(ll nh=h; nh<h+a; nh++) {
            for(ll nw=w; nw<w+b; nw++) {
                used[nh][nw] = false;
            }
        }
    };

    // 完成したか？
    // O(HW)
    auto is_complete = [&](vector<vector<bool>> &used) {
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                if (used[h][w]) continue;
                return false;
            }
        }
        return true;
    };

    auto dfs = [&](auto dfs, ll depth, vector<ll> &tiles, vector<vector<bool>> &used) {
        // 終了条件
        if (depth == N) {
            return is_complete(used);
        }

        // 今回、どのマスをターゲットにするか（ターゲットマスに、タイルの左上を合わせるように敷く）
        ll target_h, target_w;
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                if (used[h][w]) continue;
                target_h = h;
                target_w = w;
                goto BREAK1;
            }
        }
        BREAK1:

        // 今回、どのタイルを使うか
        ll tile_i = tiles[depth];

        // タイルを使わない場合の探索
        auto res1 = dfs(dfs, depth+1, tiles, used);
        if (res1) return true;

        {// タイルを普通に使う場合の探索
            bool can_use = f(target_h, target_w, A[tile_i], B[tile_i], used);
            if (can_use) {
                fill_tile(target_h, target_w, A[tile_i], B[tile_i], used);
                bool res2 = dfs(dfs, depth+1, tiles, used);
                if (res2) return true;
                unfill_tile(target_h, target_w, A[tile_i], B[tile_i], used);
            }
        }

        {// タイルを90度回転して使う場合の探索
            bool can_use = f(target_h, target_w, B[tile_i], A[tile_i], used);
            if (can_use) {
                fill_tile(target_h, target_w, B[tile_i], A[tile_i], used);
                bool res3 = dfs(dfs, depth+1, tiles, used);
                if (res3) return true;
                unfill_tile(target_h, target_w, B[tile_i], A[tile_i], used);
            }
        }

        return false;
    };

    vector used(H+1, vector(W+1, false)); // used[h][w] := マス(h,w)にタイルは敷かれているか？
    vector<ll> tiles(N); // 使うタイルの順番
    iota(tiles.begin(), tiles.end(), 0LL);
    sort(tiles.begin(), tiles.end());
    do {
        bool ans = dfs(dfs, 0, tiles, used);
        if (ans) {
            cout << "Yes" << endl;
            return;
        }
    }while (next_permutation(tiles.begin(), tiles.end()));
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}