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


int main() {
    solve();
    return 0;
}