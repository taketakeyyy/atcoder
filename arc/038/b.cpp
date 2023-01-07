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
// string vs = "URDL";  // 上右下左

ll H, W;
vector<string> S;

namespace Solver1 {
    vector<ll> vy = { 1, 1, 0};
    vector<ll> vx = { 0, 1, 1};
    vector<vector<vector<ll>>> memo; // memo[h][w][who_turn] := 現在地が(h,w)でwho_turnの番のときの勝敗のメモ

    bool is_inside(ll h, ll w) {
        return (h>=0 && h<H && w>=0 && w<W);
    }

    // minimax法
    ll minimax(ll h, ll w, ll who_turn, ll parent_score) {
        if (memo[h][w][who_turn] != 0) return memo[h][w][who_turn];

        bool can_move = false;
        ll res_score;
        if (who_turn) res_score = numeric_limits<ll>::min();
        else res_score = numeric_limits<ll>::max();

        for(ll vi=0; vi<3; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (!is_inside(nh,nw)) continue;
            if (S[nh][nw] == '#') continue;

            can_move = true;
            ll child_score = minimax(nh, nw, who_turn^1, res_score);
            if (who_turn) res_score = max(res_score, child_score);
            else res_score = min(res_score, child_score);
            // αβカット
            if (who_turn) {
                if (res_score > parent_score) break;
            }
            else {
                if (res_score < parent_score) break;
            }
        }

        if (!can_move) {
            if (who_turn) memo[h][w][who_turn] = -1;  // 後攻の勝ち
            else memo[h][w][who_turn] = 1;  // 先行の勝ち
            return memo[h][w][who_turn];
        }
        memo[h][w][who_turn] = res_score;
        return res_score;
    }

    // minimaxを使う
    // メモ化再帰を使って高速化する(TLE対策)
    void solve() {
        cin >> H >> W;
        S.resize(H);
        for(ll h=0; h<H; h++) cin >> S[h];
        memo.resize(H);
        for(ll h=0; h<H; h++) {
            memo[h].resize(W);
            for(ll w=0; w<W; w++) {
                memo[h][w].resize(2,0);
            }
        }

        set<tuple<ll,ll,ll>> visited;
        ll ans = minimax(0,0,1,100);
        if (ans == 1) cout << "First" << endl;
        else cout << "Second" << endl;
    }
}
namespace Solver2 {
    vector<ll> vy = { 1, 1, 0};
    vector<ll> vx = { 0, 1, 1};
    map<pair<ll,ll>,bool> memo; // memo[(h,w)] := 現在地が(h,w)のときの勝敗のメモ（勝つ：true）

    bool is_inside(ll h, ll w) {
        return (h>=0 && h<H && w>=0 && w<W);
    }

    // 現在地(h,w)が勝ち確ならtrueを返す
    bool judge(ll h, ll w) {
        if (memo.count({h,w})) return memo[{h,w}];

        bool res = false;
        for(ll vi=0; vi<3; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (!is_inside(nh,nw)) continue;
            if (S[nh][nw] == '#') continue;
            res |= !judge(nh, nw);  // 1手先のルートで「負け確」から戻ってこれるなら、「勝ち確」になる
        }
        return memo[{h,w}] = res;
    }

    void solve() {
        cin >> H >> W;
        S.resize(H);
        for(ll h=0; h<H; h++) cin >> S[h];

        if (judge(0,0)) cout << "First" << endl;
        else cout << "Second" << endl;
    }
}

int main() {
    // Solver1::solve();
    Solver2::solve();
    return 0;
}