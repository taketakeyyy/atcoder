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

/**
 * @brief chokudai氏の実装で勉強
 * 初期解を貪欲的に適当に作成する。その際、どのように移動したかの履歴をつくる。
 * その後、履歴の適当な区間を切り取り、スコアが上がるような別の経路がないか探索する。
 * スコアが上がる経路が見つかったら、新しい経路で履歴を継ぎ接ぎする。
 * この履歴を切り取って継ぎ接ぎするのを制限時間いっぱい繰り返す。
 *
 * @link https://atcoder.jp/contests/ahc002/submissions/28292112
 *
 */

// DFSの最大探索深さ
const ll MAX_DEPTH = 32;  // 25  // 大きすぎてもダメ?
// 探索の時間
// const clock_t MAX_CLOCK = 1800;  // ダメ
const clock_t MAX_CLOCK = 1.95 * CLOCKS_PER_SEC;
// 切り取る履歴の最大幅
const int MAX_WIDTH = 9;

const ll N = 50;
vector<vector<ll>> tiles(N, vector<ll>(N, 0));
vector<vector<ll>> points(N, vector<ll>(N, 0));
vector<ll> vy = {1, 0, -1, 0};
vector<ll> vx = {0, 1, 0, -1};
string vs = "DRUL";
// メルセンヌ・ツイスター法による疑似乱数生成器を、ハードウェア乱数をシードにして初期化
std::random_device seed_gen;
std::mt19937 engine(seed_gen());

/**
 * @brief 座標x,yがタイルの内側に収まっているかの判定
 *
 * @param y
 * @param x
 * @return true
 * @return false
 */
bool inside(ll y, ll x) {
    return y>=0 && x>=0 && y<N && x<N;
}


void dfs(ll y, ll x, ll depth, ll gy, ll gx, ll point, vector<bool> &used2, ll &best_point, vector<pair<ll,ll>> &route, vector<pair<ll,ll>> &best_route) {
    if (y == gy && x == gx) {
        // ゴールした
        if (point > best_point) {
            // ベスト更新
            best_route.resize(0);
            best_point = point;
            for(auto[y,x]: route) {
                best_route.push_back({y,x});
            }
        }
        return;
    }

    ll dist = abs(y-gy) + abs(x-gx);  // ゴールまでの距離
    if (depth + dist >= MAX_DEPTH) return;  // これ以上探索してもゴールまでたどり着けないので枝切り

    route.push_back({y,x});
    used2[tiles[y][x]] = true;

    for(ll k=0; k<4; k++) {
        // 4方向の移動を試みる
        ll ny = y + vy[k];
        ll nx = x + vx[k];
        if (!inside(ny, nx)) continue;
        if (used2[tiles[ny][nx]]) continue;
        dfs(ny, nx, depth+1, gy, gx, point+points[ny][nx], used2, best_point, route, best_route);
    }

    route.pop_back();
    used2[tiles[y][x]] = false;

    return;
}

pair<ll, vector<pair<ll,ll>>> search(ll y, ll x, ll depth, ll gy, ll gx, ll point, vector<bool> &used2) {
    ll best_point = 0;
    vector<pair<ll,ll>> route;
    vector<pair<ll,ll>> best_route;
    dfs(y, x, depth, gy, gx, point, used2, best_point, route, best_route);
    return make_pair(best_point, best_route);
}


/**
 * @brief 初期解の作成
 *
 * @param si 開始地点i
 * @param sj 開始地点j
 * @return pair<ll, vector<pair<ll,ll>>> {初期解のポイント, 初期解の移動したマスの履歴}
 */
pair<ll, vector<pair<ll,ll>>> initial_solution(ll si, ll sj) {
    vector<bool> used = vector<bool>(N*N, false);  // 訪問済みタイル番号
    used[tiles[si][sj]] = true;
    // string ans = "";

    // 幅優先的にやる
    ll y = si;
    ll x = sj;
    ll point = tiles[si][sj];
    vector<pair<ll,ll>> posL;  // 移動したマスの履歴
    posL.push_back({y, x});
    while (1) {
        ll next_move = -1;  // vy, vx, vs の添字
        ll next_point = point;

        for(ll k=0; k<4; k++) {
            ll ny = y + vy[k];
            ll nx = x + vx[k];
            if (!inside(ny, nx)) continue;
            if (used[tiles[ny][nx]]) continue;
            if (next_point > point + points[ny][nx]) continue;
            next_move = k;
            next_point = point + points[ny][nx];
        }

        if (next_move == -1) break;
        y = y + vy[next_move];
        x = x + vx[next_move];
        used[tiles[y][x]] = true;
        point += points[y][x];
        // ans += vs[next_move];
        posL.push_back({y, x});
    }

    return make_pair(point, posL);
}

void solve() {
    // 入力
    ll si, sj; cin >> si >> sj;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> tiles[i][j];
        }
    }
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> points[i][j];
        }
    }

    // クロックスタート
    clock_t clock_start = clock();

    // 初期解を作成し、履歴を作る
    auto [point, posL] = initial_solution(si, sj);

    // 時間の限り探索
    while(clock() - clock_start < MAX_CLOCK) {
        // 履歴の[start+1, end]の範囲を、より良い経路を再度探索する感じ
        std::uniform_int_distribution<> dist1(0, (int)posL.size()-1);  // [0, posL.size()-1]
        ll start = dist1(engine);
        std::uniform_int_distribution<> dist2(0, (int)MAX_WIDTH);  // [0, 9]
        ll end = (ll)start + 1LL + (ll)dist2(engine);  // [start+1, start+10]
        if (end >= (ll)posL.size()) continue;

        // 履歴の[start+1, end]の経路マスのみ訪問してないことにする（他の経路はそのまま）
        vector used2 = vector<bool>(N*N, false);  // 訪問済みのタイル番号はtrue
        for(ll i=0; i<(ll)posL.size(); i++) {
            if (i <= start || i > end) {
                // 経路を作り直さない部分は訪問済みにしておく
                used2[tiles[posL[i].first][posL[i].second]] = true;
            }
            else {
                // 経路を作り直す部分のポイントは引いておく
                point -= points[posL[i].first][posL[i].second];
            }
        }

        // より良い経路をDFSで探索
        auto [best_point, best_route] = search(posL[start].first, posL[start].second, 0, posL[end].first, posL[end].second, 0, used2);

        if (best_point == 0) continue;  // より良い解が見つからなかったとき

        // 履歴を更新する
        vector<pair<ll,ll>> NposL;  // 新しい履歴
        for(ll i=0; i<start; i++) {
            NposL.emplace_back(posL[i]);
        }
        for(auto[y, x]: best_route) {
            // NposL.emplace_back({y, x});
            NposL.push_back({y,x});
        }
        for(ll i=end; i<(ll)posL.size(); i++) {
            NposL.emplace_back(posL[i]);
        }
        point += best_point;
        posL = NposL;
    }

    // 出力
    string ans = "";
    vector used3 = vector<bool>(N*N, false);
    for(ll i=0; i<(ll)posL.size()-1; i++) {
        bool is_ok = false;  // 出力がバグっていたら追加を打ち切るフラグ
        used3[tiles[posL[i].first][posL[i].second]] = true;

        if (used3[tiles[posL[i+1].first][posL[i+1].second]]) break;

        for(ll k=0; k<4; k++) {
            if (posL[i].first+vy[k]==posL[i+1].first && posL[i].second+vx[k]==posL[i+1].second) {
                is_ok = true;
                ans += vs[k];
            }
        }
        if (!is_ok) break;
    }
    printf("%s\n", ans.c_str());
}


int main() {
    solve();
    return 0;
}