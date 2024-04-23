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

// ノード
struct Node {
    ll eval;  // 評価値
    ll h;   // h座標
    ll w;   // w座標
};

// マスの色
enum class Color {
    EMPTY = 0,
    ME = 1,
    ENEMY = 2,
};

// ジャッジの結果
enum class JudgeResult {
    CONTINUE = 0, // ゲーム続行（決着はついてない）
    ME = 1, // 高橋WIN
    ENEMY = 2, // 青木WIN
    DRAW = 3, // 引き分け
};

// 誰のターン
enum class Turn {
    ME = 1, // 高橋
    ENEMY = 2, // 青木
};

JudgeResult judge(const vector<vector<ll>> &A, vector<vector<Color>> &grid) {
    {// 横方向に連続して色が塗られているか？
        for(ll i=0; i<3; i++) {
            Color col = grid[i][0];
            if (col == Color::EMPTY) continue;
            bool is_game_over = true;
            for(ll j=1; j<3; j++) {
                if (col==grid[i][j]) continue;
                is_game_over = false;
            }
            if (is_game_over) {
                if (col == Color::ME) return JudgeResult::ME;
                if (col == Color::ENEMY) return JudgeResult::ENEMY;
            }
        }
    }
    {// 縦方向
        for(ll j=0; j<3; j++) {
            Color col = grid[0][j];
            if (col == Color::EMPTY) continue;
            bool is_game_over = true;
            for(ll i=1; i<3; i++) {
                if (col==grid[i][j]) continue;
                is_game_over = false;
            }
            if (is_game_over) {
                if (col == Color::ME) return JudgeResult::ME;
                if (col == Color::ENEMY) return JudgeResult::ENEMY;
            }
        }
    }
    {// 斜め
        if (grid[0][0]==grid[1][1] and grid[1][1]==grid[2][2] and grid[0][0]!=Color::EMPTY) {
            if (grid[0][0]==Color::ME) return JudgeResult::ME;
            if (grid[0][0]==Color::ENEMY) return JudgeResult::ENEMY;
        }
        if (grid[0][2]==grid[1][1] and grid[1][1]==grid[2][0] and grid[0][2]!=Color::EMPTY) {
            if (grid[0][2]==Color::ME) return JudgeResult::ME;
            if (grid[0][2]==Color::ENEMY) return JudgeResult::ENEMY;
        }
    }
    {// すべて色塗られているか？
        bool is_game_over = true;
        for(ll i=0; i<3; i++) {
            for(ll j=0; j<3; j++) {
                if (grid[i][j]!=Color::EMPTY) continue;
                is_game_over = false;
            }
        }
        if (is_game_over) {
            // 色が塗られているところの得点が高いほうが勝ち
            ll taka = 0;
            ll aoki = 0;
            for(ll i=0; i<3; i++) {
                for(ll j=0; j<3; j++) {
                    if (grid[i][j]==Color::ME) taka += A[i][j];
                    if (grid[i][j]==Color::ENEMY) aoki += A[i][j];
                }
            }
            if (taka > aoki) return JudgeResult::ME;
            else return JudgeResult::ENEMY;
        }
    }
    return JudgeResult::CONTINUE; // 未決着（試合続行）
}

// minimaxの評価関数
Node score(JudgeResult jr, ll depth, ll h, ll w) {
    if (jr == JudgeResult::ME) {
        // 自分WIN
        return {100-depth, h, w};
    }
    else if (jr == JudgeResult::ENEMY) {
        // 相手WIN
        return {-100+depth, h, w};
    }
    return {-999, -999, -999}; // ありえない値
}

// マス(h,w)に石を置けるか？
bool is_puttable_stone(vector<vector<Color>> &grid, ll h, ll w) {
    return (grid[h][w] == Color::EMPTY);
}

// マス(h,w)に石を置く
void put_stone(vector<vector<Color>> &grid, ll h, ll w, Turn who_turn) {
    if (who_turn == Turn::ME) grid[h][w] = Color::ME;
    if (who_turn == Turn::ENEMY) grid[h][w] = Color::ENEMY;
}

// 石を取り除く
void remove_stone(vector<vector<Color>> &grid, ll h, ll w) {
    grid[h][w] = Color::EMPTY;
}

// 高橋:1 青木:2
Node minimax(const vector<vector<ll>> &A, vector<vector<Color>> &grid, Turn who_turn, ll depth, ll h, ll w) {
    // 深さ制限 || 決着がついたら終了
    JudgeResult jr = judge(A, grid);
    if (jr != JudgeResult::CONTINUE) {
        // 決着
        return score(jr, depth,  h, w);
    }

    if (who_turn == Turn::ME) {
        // 自分のターンでは、最善手を見つける
        Node res_node = Node(-INF, 99, 99);
        for(ll nh=0; nh<3; nh++) {
            for (ll nw=0; nw<3; nw++) {
                if (!is_puttable_stone(grid, nh, nw)) { continue; }
                put_stone(grid, nh, nw, who_turn);
                Turn nxt_turn = (who_turn==Turn::ME) ? Turn::ENEMY : Turn::ME;
                Node child_node = minimax(A, grid, nxt_turn, depth+1, nh, nw);
                if (child_node.eval > res_node.eval)  {
                    // より良い手が見つかったらノードを更新
                    // h,wはここで代入する。res_node = child_nodeとすると最深ノードの手が返ってくる
                    res_node = Node(child_node.eval, nh, nw); // h,wはここで代入
                }
                remove_stone(grid, nh, nw);
            }
        }
        return res_node;
    }
    else {
        // 相手のターンでは、最悪手（相手にとって最善手）を見つける
        Node res_node = Node(INF, 99, 99);
        for(ll nh=0; nh<3; nh++) {
            for (ll nw=0; nw<3; nw++) {
                if (!is_puttable_stone(grid, nh, nw)) { continue; }
                put_stone(grid, nh, nw, who_turn);
                Turn nxt_turn = (who_turn==Turn::ME) ? Turn::ENEMY : Turn::ME;
                Node child_node = minimax(A, grid, nxt_turn, depth+1, nh, nw);
                if (child_node.eval < res_node.eval) {
                    // より悪い手が見つかったらノードを更新
                    res_node = Node(child_node.eval, nh, nw ); // h,wはここで代入
                }
                remove_stone(grid, nh, nw);
            }
        }
        return res_node;
    }
}

void solve() {
    vector A(3, vector(3, 0LL));
    for(ll i=0; i<3; i++) {
        for(ll j=0; j<3; j++) {
            cin >> A[i][j];
        }
    }
    vector grid(3, vector(3, Color::EMPTY));
    bool taka_win = false;
    Node res_node = minimax(A, grid, Turn::ME, 0, 99, 99);
    if (res_node.eval > 0) taka_win = true;
    if (taka_win) {
        cout << "Takahashi" << endl;
    }
    else {
        cout << "Aoki" << endl;
    }
}


// 解説AC
// メモ化DFS
void solve2() {
    vector A(3, vector(3, 0LL));
    for(ll i=0; i<3; i++) {
        for(ll j=0; j<3; j++) {
            cin >> A[i][j];
        }
    }
    const ll TAKA = 1;
    const ll AOKI = 2;
    const ll EMPTY = 0;
    const ll CONTINUE = 0;

    // 勝敗をジャッジする
    auto judge = [&](vector<vector<ll>> const &grid) {
        {// 横方向に連続して色が塗られているか？
            for(ll i=0; i<3; i++) {
                ll col = grid[i][0];
                if (col == EMPTY) continue;
                bool is_game_over = true;
                for(ll j=1; j<3; j++) {
                    if (col==grid[i][j]) continue;
                    is_game_over = false;
                }
                if (is_game_over) {
                    if (col == TAKA) return TAKA;
                    if (col == AOKI) return AOKI;
                }
            }
        }
        {// 縦方向
            for(ll j=0; j<3; j++) {
                ll col = grid[0][j];
                if (col == EMPTY) continue;
                bool is_game_over = true;
                for(ll i=1; i<3; i++) {
                    if (col==grid[i][j]) continue;
                    is_game_over = false;
                }
                if (is_game_over) {
                    if (col == TAKA) return TAKA;
                    if (col == AOKI) return AOKI;
                }
            }
        }
        {// 斜め
            if (grid[0][0]==grid[1][1] and grid[1][1]==grid[2][2] and grid[0][0]!=EMPTY) {
                if (grid[0][0]==TAKA) return TAKA;
                if (grid[0][0]==AOKI) return AOKI;
            }
            if (grid[0][2]==grid[1][1] and grid[1][1]==grid[2][0] and grid[0][2]!=EMPTY) {
                if (grid[0][2]==TAKA) return TAKA;
                if (grid[0][2]==AOKI) return AOKI;
            }
        }
        {// すべて色塗られているか？
            bool is_game_over = true;
            for(ll i=0; i<3; i++) {
                for(ll j=0; j<3; j++) {
                    if (grid[i][j]!=EMPTY) continue;
                    is_game_over = false;
                }
            }
            if (is_game_over) {
                // 色が塗られているところの得点が高いほうが勝ち
                ll taka = 0;
                ll aoki = 0;
                for(ll i=0; i<3; i++) {
                    for(ll j=0; j<3; j++) {
                        if (grid[i][j]==TAKA) taka += A[i][j];
                        if (grid[i][j]==AOKI) aoki += A[i][j];
                    }
                }
                if (taka > aoki) return TAKA;
                else return AOKI;
            }
        }
        return CONTINUE; // 未決着（試合続行）
    };

    vector grid(3, vector(3, 0LL)); // grid[i][j] := マス(i,j)の色（taka:1, aoki:2, empty:0）
    map<vector<vector<ll>>, ll> memo; // memo[S] := 盤面Sのときの勝敗のメモ値（taka:1, aoki:2）
    auto dfs = [&](auto dfs, vector<vector<ll>> &grid, ll turn) {
        // 勝敗ジャッジ
        if (memo.contains(grid)) return memo[grid];
        ll jr = judge(grid);
        if (jr != CONTINUE) {
            return jr;
        }

        // 次の探索
        for(ll i=0; i<3; i++) {
            for(ll j=0; j<3; j++) {
                if (grid[i][j] != EMPTY) continue;
                grid[i][j] = turn;
                ll nxt_turn = turn==TAKA ? AOKI : TAKA;
                ll res = dfs(dfs, grid, nxt_turn);
                grid[i][j] = EMPTY;
                if (res == turn) {
                    // 遷移先の盤面で1個でも今回のターンの人間が勝つ盤面があるならば、この盤面はこのターンの人間の勝利が確定
                    return memo[grid] = turn;
                }
            }
        }
        // 遷移先の盤面で1個もこのターンの人間が勝つ盤面がなければ、相手の勝利が確定
        return memo[grid] = (turn==TAKA ? AOKI : TAKA);
    };
    dfs(dfs, grid, TAKA);
    if (memo[grid] == TAKA) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}

// 解説AC
// NegaMax
void solve3() {
    vector A(3, vector(3, 0LL));
    for(ll i=0; i<3; i++) {
        for(ll j=0; j<3; j++) {
            cin >> A[i][j];
        }
    }
    const ll WIN = 1;
    const ll LOSE = -1;
    const ll CONTINUE = 0;
    const ll EMPTY = -1;

    // 勝敗をジャッジする
    auto judge = [&](vector<vector<ll>> const &grid, ll who_turn) {
        {// 横方向に連続して色が塗られているか？
            for(ll i=0; i<3; i++) {
                ll col = grid[i][0];
                if (col == EMPTY) continue;
                bool is_game_over = true;
                for(ll j=1; j<3; j++) {
                    if (col==grid[i][j]) continue;
                    is_game_over = false;
                }
                if (is_game_over) {
                    if (col == who_turn) return WIN;
                    else return LOSE;
                }
            }
        }
        {// 縦方向
            for(ll j=0; j<3; j++) {
                ll col = grid[0][j];
                if (col == EMPTY) continue;
                bool is_game_over = true;
                for(ll i=1; i<3; i++) {
                    if (col==grid[i][j]) continue;
                    is_game_over = false;
                }
                if (is_game_over) {
                    if (col == who_turn) return WIN;
                    else return LOSE;
                }
            }
        }
        {// 斜め
            if (grid[0][0]==grid[1][1] and grid[1][1]==grid[2][2] and grid[0][0]!=EMPTY) {
                if (grid[0][0]==who_turn) return WIN;
                else return LOSE;
            }
            if (grid[0][2]==grid[1][1] and grid[1][1]==grid[2][0] and grid[0][2]!=EMPTY) {
                if (grid[0][2]==who_turn) return WIN;
                else return LOSE;
            }
        }
        {// すべて色塗られているか？
            bool is_game_over = true;
            for(ll i=0; i<3; i++) {
                for(ll j=0; j<3; j++) {
                    if (grid[i][j]!=EMPTY) continue;
                    is_game_over = false;
                }
            }
            if (is_game_over) {
                // 色が塗られているところの得点が高いほうが勝ち
                ll me = 0;
                ll enemy = 0;
                for(ll i=0; i<3; i++) {
                    for(ll j=0; j<3; j++) {
                        if (grid[i][j]==who_turn) me += A[i][j];
                        else enemy += A[i][j];
                    }
                }
                if (me > enemy) return WIN;
                else return LOSE;
            }
        }
        return CONTINUE; // 未決着（試合続行）
    };

    vector grid(3, vector(3, EMPTY)); // grid[i][j] := マス(i,j)の色（taka:0, aoki:1, empty:-1）
    map<vector<vector<ll>>, ll> memo; // memo[S] := 盤面Sのときのスコアのメモ値
    auto negamax = [&](auto negamax, vector<vector<ll>> &grid, ll who_turn, ll alpha) {
        // 勝敗ジャッジ
        if (memo.contains(grid)) return memo[grid];
        ll jr = judge(grid, who_turn);
        if (jr != CONTINUE) {
            memo[grid] = jr;
            return memo[grid];
        }

        // 次の探索
        ll mx = -INF;
        for(ll i=0; i<3; i++) {
            for(ll j=0; j<3; j++) {
                if (grid[i][j] != EMPTY) continue;
                grid[i][j] = who_turn;
                ll res = -negamax(negamax, grid, who_turn^1LL, mx);
                grid[i][j] = EMPTY;
                mx = max(mx, res);
                if (alpha >= -mx) { // αカット
                    return mx; // 枝狩りするときは最適値ではないのでメモしない
                }
            }
        }
        return memo[grid] = mx;
    };
    negamax(negamax, grid, 0, -INF);
    if (memo[grid] == WIN) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}