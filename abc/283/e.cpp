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

bool is_inside(ll i, ll j) {
    return (0<=i && i<H && 0<=j && j<W);
}

// i行目に孤立したマスがあるかどうかを返す
bool exist_isolation(ll i, vector<vector<ll>> &A) {
    for(ll j=0; j<W; j++) {
        bool is_iso = true;
        for(ll nxt=0; nxt<4; nxt++) {
            ll ni = i+vy[nxt];
            ll nj = j+vx[nxt];
            if (!is_inside(ni, nj)) continue;

            if (A[ni][nj] == A[i][j]) {
                is_iso = false;
                break;
            }
        }
        if (is_iso) return true;
    }
    return false;
}

// i行目を反転させる
void flipA(ll i, vector<vector<ll>> &A) {
    for(ll j=0; j<W; j++) A[i][j] ^= 1;
}

// ある行を反転したときの影響は、その行と上下の3行しかない。
// いま、i行目に注目しているとする。i行目より上に孤立したマスは存在しない。
// i行目に孤立したマスがない場合、なにもしなくていい。
// i行目に孤立したマスがある場合、
//   * i行目を反転させる
//   * i+1行目を反転させる
// のどちらかをするべきである。
// 操作回数は最小にしたいので、
//   * i+1行目を反転させて、i,i+1,i+2行目に孤立したマスがなくなるなら、これをする
//   * i+1行目を反転させて、i,i+1行目に孤立したマスがなくなるなら、これをする
//   * i行目を反転させて、i-1,i行目に孤立したマスがなくなるなら、これをする
//
// 上から反転するかどうかをシミュレーションで解く。
// WA笑
void solve() {
    cin >> H >> W;
    vector<vector<ll>> A(H, vector<ll>(W));
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            cin >> A[i][j];
        }
    }

    // 孤立したマスがある行は、反転する
    ll ans = 0;
    for(ll i=0; i<H; i++) {
        // 孤立したマスがないならスキップ
        if (!exist_isolation(i, A)) continue;  // なにかおかしい（入力例3の1行目）

        // このi行目には孤立したマスが存在する
        if (i+1 < H) {
            // i+1行目を反転させて孤立マスがなくなるか？
            flipA(i+1, A);
            bool is_ok1, is_ok2;
            is_ok1 = !exist_isolation(i, A);
            is_ok2 = !exist_isolation(i+1, A);

            if (is_ok1 && is_ok2) {
                ans++; i+=1;
                continue;
            }
            // 元に戻す
            flipA(i+1, A);
        }
        // i行目を反転させて孤立マスがなくなるか？
        flipA(i, A);
        bool is_ok1, is_ok2;
        is_ok1 = !exist_isolation(i, A);
        if (i-1 >= 0) is_ok2 = !exist_isolation(i-1, A);
        else is_ok2 = true;

        if (is_ok1 && is_ok2) {
            ans++; continue;
        }
        else {
            cout << -1 << endl;
            return;
        }
    }

    // 出力
    cout << ans << endl;
}

// 解説AC
// i行目を反転させたときの影響は、i-1行目、i行目、i+1行目の3行しかない。
// ということは上から順に反転するかどうかを埋めていくことができる。これはDP。
// dp[i][state] := i行目まで決めて、状態がstateのときの最小回数
// stateは、「i行目を反転するかどうか」「i+1行目を反転するかどうか」の00,01,10,11の4状態
void solve2() {
    ll H, W; cin >> H >> W;
    vector A(H, vector<ll>(W));
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) cin >> A[i][j];
    }

    // A[i]を返す。do_flip=trueなら反転して返す。
    auto get = [&](ll i, bool do_flip) {
        vector<ll> res = A[i];
        if (do_flip) {
            for(ll j=0; j<W; j++) res[j] ^= 1;
        }
        return res;
    };
    // A0行目
    // A1行目
    // A2行目
    // とした場合、
    // A1に孤立マスが存在しないかのチェック関数（孤立してないならtrueを返す）
    auto check = [&](vector<ll> const &A0, vector<ll> const &A1, vector<ll> const &A2) {
        for(ll j=0; j<W; j++) {
            if (A0[j] == A1[j]) continue;  // A1[j]の上が同じ値なら、j列目は孤立してない
            if (A2[j] == A1[j]) continue;  // A1[j]の下が同じ値なら、j列目は孤立してない
            if (j-1>=0 && A1[j-1] == A1[j]) continue;  // 左が同じ値なら、孤立してない
            if (j+1<W && A1[j+1]==A1[j]) continue;  // 右が同じ値なら、孤立してない
            return false;
        }
        return true;
    };

    vector<ll> dp(4, INF);  // 注目行とその下の行の、反転状態
    // 最初の2行は遷移がむずかしいので全探索する
    for(ll state=0; state<4; state++) {
        vector<ll> A0(W,-1);  // -1行目（便宜上）
        auto A1 = get(0, state&2);  // 0行目
        auto A2 = get(1, state&1);  // 1行目
        ll cnt = 0;  // 反転回数
        if (state&1) cnt++;
        if (state&2) cnt++;
        if (check(A0,A1,A2)) dp[state] = cnt;
    }

    // 2行目以降はdp
    for(ll i=2; i<H; i++) {
        vector<ll> olddp(4, INF);
        swap(olddp, dp);
        for(ll state=0; state<4; state++) {
            auto A0 = get(i-2, state&2);  // 1行上
            auto A1 = get(i-1, state&1);  // 注目行
            for(ll x=0; x<2; x++) {// 1行下を反転するかしないかの2状態を探索
                auto A2 = get(i,x);  // 1行下
                if (check(A0,A1,A2)) {
                    ll nstate = (state&1)<<1 | x;
                    dp[nstate] = min(dp[nstate], olddp[state]+x);
                }
            }
        }
    }

    // 最後の行のチェック
    ll ans = INF;
    for(ll state=0; state<4; state++) {
        auto A0 = get(H-2, state&2);  // 1行上
        auto A1 = get(H-1, state&1);  // 注目行
        vector<ll> A2(W, -1);  // 1行下（便宜上）
        if (check(A0,A1,A2)) ans = min(ans, dp[state]);
    }
    if (ans == INF) ans = -1;
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}