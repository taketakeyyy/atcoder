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

ll H, W;
vector<vector<ll>> A;
vector<vector<ll>> memo;  // memo[i][j] := f(i,j)のメモ値
vector<vector<bool>> visited;  // memo[i][j]にメモしたかどうか

// (i,j)にいるときに手番を持っている人を「自分」とする（「自分」は高橋かもしれないし青木かもしれない）
// f(i,j) := (i,j)からスタートしたとき、(自分-相手)の最大値
ll f(ll i, ll j) {
    if (i == H-1 && j==W-1) return 0;
    if (visited[i][j]) return memo[i][j];
    visited[i][j] = true;

    ll res = -INF;
    if (j+1 < W) {//右へ移動
        res = max(res, A[i][j+1]-f(i,j+1));  // 正負を反転させる（自分と相手が入れ替わるので）
    }
    if (i+1 < H) {//下へ移動
        res = max(res, A[i+1][j]-f(i+1,j));
    }
    return memo[i][j] = res;
}

// メモ化再帰（negamax法みたいだな？）
void solve() {
    cin >> H >> W;
    A.resize(H);
    for(ll i=0; i<H; i++) {
        A[i].resize(W);
        for(ll j=0; j<W; j++) {
            char c; cin >> c;
            A[i][j] = (c=='+') ? 1 : -1;
        }
    }

    memo.resize(H);
    visited.resize(H);
    for(ll i=0; i<H; i++) {
        memo[i].resize(W);
        visited[i].resize(W, false);
    }
    ll score = f(0,0);
    if (score == 0) cout << "Draw" << endl;
    else if (score < 0) cout << "Aoki" << endl;
    else cout << "Takahashi" << endl;
}


// 解説のNegaAlpha法 (negamaxのαカット実装）
void solve2() {
    ll H, W; cin >> H >> W;
    vector A(H, vector(W, 0LL));
    for(ll h=0; h<H; h++) {
        string s; cin >> s;
        for(ll w=0; w<W; w++) {
            if (s[w]=='-') A[h][w] = -1;
            else A[h][w] = 1;
        }
    }

    // 移動用（右,下）
    const vector<ll> vy = { 0, 1,};
    const vector<ll> vx = { 1, 0,};

    // マス内に収まっているか？
    auto is_inside = [&](ll h, ll w) {
        return (h>=0 and h<H and w>=0 and w<W);
    };

    // NegaMax法
    // negamax(h,w) := 現在のマス(h,w)からスタートして、そのときの手番がxのとき、互いが最適に行動したときの(xのスコア - yのスコア)の最大値
    vector memo(H, vector(W, 0LL)); // memo[i][j] := マス(i,j)のnegamaxのメモ値
    vector visited(H, vector(W, false));
    auto negamax = [&](auto negamax, ll h, ll w, ll alpha, ll who_turn) {
        // 終了条件
        if (visited[h][w]) return memo[h][w];
        visited[h][w] = true;
        if (h==H-1 and w==W-1) {
            memo[h][w] = 0LL;
            if (who_turn==1) memo[h][w] *= -1; // 相手の手番で葉ノードになったら符号反転
            return memo[h][w];
        }

        // 次の探索
        ll mx = -INF;
        for(ll vi=0; vi<2; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (!is_inside(nh,nw)) continue;
            ll new_score = A[nh][nw]-negamax(negamax, nh, nw, mx, who_turn^1);
            mx = max(mx, new_score);
            if (alpha-2LL >= -mx) break; // αカット（-2LLは幅を持たせている）
        }

        return memo[h][w] = mx;
    };

    // 答え
    ll ans = negamax(negamax, 0, 0, -INF, 0);
    if (ans == 0) cout << "Draw" << endl;
    else if (ans > 0) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}