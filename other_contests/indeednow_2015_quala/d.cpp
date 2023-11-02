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

// 24手を全探索を考える。常に4方向移動でき、手戻りするような移動はしないとすると、4*3^{23}
// これはTLEする。
// 空白マスに注目する。
// 初期状態の空白マスから12手以内を全探索する。4*3^{12}=2*10^6
// 終了状態の空白マスから12手以内を全探索する。
// 半分全列挙で、最小となる操作数を探す。
void solve() {
    int H, W; cin >> H >> W;
    vector<vector<int>> grid(H, vector<int>(W));
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            cin >> grid[h][w];
        }
    }
    // パズル完成時の状態
    vector<vector<int>> perfect_grid(H, vector<int>(W));
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) perfect_grid[h][w] = h*W + (w+1);
    }
    perfect_grid[H-1][W-1] = 0;

    // 座標(h,w)はグリッド内に収まっているか？
    auto is_inside = [&](int h, int w) -> bool{
        return (0<=h && h<H && 0<=w && w<W);
    };

    // mp[s] := パズルの状態sにするための最短手数
    auto genMap = [&](vector<vector<int>> init_grid, int depth_limit) {
        // 空白マスの場所を探す
        int init_h=-1, init_w=-1;
        for(int h=0; h<H; h++) {
            for(int w=0; w<W; w++) {
                if (init_grid[h][w] == 0) {
                    init_h = h; init_w = w;
                }
            }
        }

        // mpを作る
        map<vector<vector<int>>, int> mp;
        mp[init_grid] = 0;
        deque<tuple<int,int,int,vector<vector<int>>>> deq; // (手数,空白マスのh座標,空白マスのw座標,状態)
        deq.push_back({0, init_h, init_w, init_grid});
        while(!deq.empty()) {
            auto[cost, h, w, now_grid] = deq.front(); deq.pop_front();

            if (cost==depth_limit+1) continue;

            for(int vi=0; vi<4; vi++) {
                int nh = h + vy[vi];
                int nw = w + vx[vi];
                if (!is_inside(nh, nw)) continue;
                swap(now_grid[h][w], now_grid[nh][nw]);
                if (!mp.count(now_grid)) {
                    mp[now_grid] = cost+1;
                    deq.push_back({cost+1, nh, nw, now_grid});
                }
                swap(now_grid[h][w], now_grid[nh][nw]);
            }
        }
        return mp;
    };
    auto mp1 = genMap(grid, 11); // 初期状態から11手以内を探索
    auto mp2 = genMap(perfect_grid, 12); // 完成状態から12手以内を探索

    // パズルを解くための最小手数を求める
    // 23手以内の最小手数を探す。なければ答えは24（MLE対策）
    int ans = 24;
    for(auto[state1, val1]: mp1) {
        if (!mp2.count(state1)) continue;
        ans = min(ans, val1 + mp2[state1]);
    }
    cout << ans << endl;
}


// A*アルゴリズム
void solve2() {
    int H, W; cin >> H >> W;
    vector<vector<int>> grid(H, vector<int>(W));
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            cin >> grid[h][w];
        }
    }

    // 最初の0の場所を探す
    int init_h, init_w;
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            if (grid[h][w] == 0) {
                init_h = h; init_w = w;
            }
        }
    }

    // 各番号の完成形とのマンハッタン距離の総和を完成までの推定コストとして、それを計算する
    auto estimate_cost = [&](vector<vector<int>> &grid) -> int {
        unordered_map<int,pair<int,int>> mp;
        for(int h=0; h<H; h++) {
            for(int w=0; w<W; w++) {
                mp[grid[h][w]] = {h,w};
            }
        }

        int res = 0; // 推定コストの総和
        for(int h=0; h<H; h++) {
            for(int w=0; w<W; w++) {
                int num = h*W + w + 1;
                if (num == H*W) num = 0;
                // if (num == H*W) continue;
                auto[h1, w1] = mp[num];
                res += abs(h-h1) + abs(w-w1);
            }
        }
        return res/2;
    };

    // グリッド内に収まっているか？
    auto is_inside = [&](int h, int w) -> bool {
        return (0<=h && h<H && 0<=w && w<W);
    };

    // 完成したかのチェック
    auto is_clear = [&](const vector<vector<int>> &grid) -> bool {
        for(int h=0; h<H; h++) {
            for(int w=0; w<W; w++) {
                if (h==H-1 && w==W-1) {
                    if (grid[h][w] != 0) return false;
                }
                else {
                    if (grid[h][w] != h*W+w+1) return false;
                }
            }
        }
        return true;
    };

    // A*アルゴリズム
    // トータルコスト = 現在の手数 + 完成までの推定コスト
    // priority_queue<tuple<int,int,int,int,vector<vector<int>>>, vector<tuple<int,int,int,int,vector<vector<int>>>>, greater<>> pq;  // 小さい順を維持する優先度付きキュー
    // pq.push({estimate_cost(grid), 0, init_h, init_w, grid}); // (トータルコスト, 現在の手数, h座標, w座標, グリッドの状態)
    priority_queue<tuple<int,int,int,vector<vector<int>>>, vector<tuple<int,int,int,vector<vector<int>>>>, greater<>> pq;  // 小さい順を維持する優先度付きキュー
    pq.push({0, init_h, init_w, grid}); // (現在の手数, h座標, w座標, グリッドの状態)
    set<vector<vector<int>>> visited;
    visited.insert(grid);
    int ans = 24;
    while(!pq.empty()) {
        auto[cost, h, w, now_grid] = pq.top(); pq.pop();

        if (is_clear(now_grid)) {
            ans = min(ans, cost);
        }

        for(int vi=0; vi<4; vi++) {
            int nh = h + vy[vi];
            int nw = w + vx[vi];
            if (!is_inside(nh,nw)) continue;
            swap(now_grid[h][w], now_grid[nh][nw]);
            if (!visited.count(now_grid)) {
                visited.insert(now_grid);
                int ecost = estimate_cost(now_grid);
                if (ecost+cost <= ans) { // 現在の手数 + 完成までの推定コスト <= 現在の最短手数
                // if (ecost <= 24-cost) { // 完成までの推定コスト <= 残り手数数ならプッシュ
                    pq.push({cost+1, nh, nw, now_grid});
                }
            }
            swap(now_grid[h][w], now_grid[nh][nw]);
        }
    }
    cout << ans << endl;
}


// A*アルゴリズム
void solve3() {
    int H, W; cin >> H >> W;
    vector<vector<int>> grid(H, vector<int>(W));
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            cin >> grid[h][w];
        }
    }

    // 最初の0の場所を探す
    int init_h, init_w;
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            if (grid[h][w] == 0) {
                init_h = h; init_w = w;
            }
        }
    }

    // 各番号の完成形とのマンハッタン距離の総和を完成までの推定コストとして、それを計算する
    auto estimate_cost = [&](vector<vector<int>> &grid) -> int {
        unordered_map<int,pair<int,int>> mp;
        for(int h=0; h<H; h++) {
            for(int w=0; w<W; w++) {
                mp[grid[h][w]] = {h,w};
            }
        }

        int res = 0; // 推定コストの総和
        for(int h=0; h<H; h++) {
            for(int w=0; w<W; w++) {
                int num = h*W + w + 1;
                if (num == H*W) num = 0;
                // if (num == H*W) continue;
                auto[h1, w1] = mp[num];
                res += abs(h-h1) + abs(w-w1);
            }
        }
        return res/2;
        // return res;
    };

    // グリッド内に収まっているか？
    auto is_inside = [&](int h, int w) -> bool {
        return (0<=h && h<H && 0<=w && w<W);
    };

    // 完成したかのチェック
    auto is_clear = [&](const vector<vector<int>> &grid) -> bool {
        for(int h=0; h<H; h++) {
            for(int w=0; w<W; w++) {
                if (h==H-1 && w==W-1) {
                    if (grid[h][w] != 0) return false;
                }
                else {
                    if (grid[h][w] != h*W+w+1) return false;
                }
            }
        }
        return true;
    };

    // A*アルゴリズム
    // トータルコスト = 現在の手数 + 完成までの推定コスト
    priority_queue<tuple<int,int,int,int,vector<vector<int>>>, vector<tuple<int,int,int,int,vector<vector<int>>>>, greater<>> pq;  // 小さい順を維持する優先度付きキュー
    pq.push({estimate_cost(grid), 0, init_h, init_w, grid}); // (トータルコスト, 現在の手数, h座標, w座標, グリッドの状態)
    // priority_queue<tuple<int,int,int,vector<vector<int>>>, vector<tuple<int,int,int,vector<vector<int>>>>, greater<>> pq;  // 小さい順を維持する優先度付きキュー
    // pq.push({0, init_h, init_w, grid}); // (現在の手数, h座標, w座標, グリッドの状態)
    map<vector<vector<int>>,int> dist; // dist[s] := 状態sへの最短手数
    dist[grid] = 0;
    int ans = 24;
    while(!pq.empty()) {
        auto[total_cost, cost, h, w, now_grid] = pq.top(); pq.pop();

        if (dist.count(now_grid) && dist[now_grid] < cost) continue;
        if (is_clear(now_grid)) {
            ans = min(ans, cost);
            continue;
        }

        for(int vi=0; vi<4; vi++) {
            int nh = h + vy[vi];
            int nw = w + vx[vi];
            if (!is_inside(nh,nw)) continue;
            swap(now_grid[h][w], now_grid[nh][nw]);
            if (!dist.count(now_grid) || dist[now_grid] > cost+1) {
                dist[now_grid] = cost+1;
                int ecost = estimate_cost(now_grid);
                // if (ecost+cost <= ans) { // 現在の手数 + 完成までの推定コスト <= 現在の最短手数
                if (ecost <= 24-cost) { // 完成までの推定コスト <= 残り手数数ならプッシュ
                    pq.push({ecost+cost+1, cost+1, nh, nw, now_grid});
                }
            }
            swap(now_grid[h][w], now_grid[nh][nw]);
        }
    }
    cout << ans << endl;
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}