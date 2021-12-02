#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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

ll N;
vector<char> C;
vector<vector<ll>> tree;
vector<vector<ll>> dp;  // 木DP：dp[i][j] := （頂点iを根とする部分木において、）頂点iを含む連結成分の状態がjのとき（j=0: aしかない, j=1: bしかない j=2: a,b両方ある）の通り数

void dfs(ll u, ll parent) {
    ll val1 = 1, val2 = 1;

    if (C[u] == 'a') {
        for (auto v: tree[u]) {
            if (v == parent) continue;
            dfs(v, u);

            ll tmp1 = (dp[v][0] + dp[v][2]);   // 「頂点uを含む連結成分の状態が0の場合」 = 「子の部分木が'a'しかない場合（連結する）」 + 「子の部分木が'a''b'両方ある場合（連結しない）」（「子の部分木が'b'しかない場合」は、uが状態0じゃなくなるので存在しない）
            ll tmp2 = (dp[v][0] + dp[v][1] + 2*dp[v][2]);  // 「頂点uを含む連結成分の状態が2の場合」 = 「子の部分木が'a'しかない場合（連結する）」+「子の部分木が'b'しかない場合（連結する）」+「子の部分木が'a''b'両方ある場合（連結してもしなくてもOK）」
            val1 *= (tmp1%MOD);
            val2 *= (tmp2%MOD);
            val1 %= MOD;
            val2 %= MOD;
        }
        dp[u][0] = val1;
        dp[u][2] = (val2 - val1 + MOD) % MOD;  // val1の分を除く（包含関係にあるので）
    }
    else {  // 'b' のとき（以下は'a'のときと同様）
        for (auto v: tree[u]) {
            if (v == parent) continue;
            dfs(v, u);

            ll tmp1 = (dp[v][1] + dp[v][2]);
            ll tmp2 = (dp[v][0] + dp[v][1] + 2*dp[v][2]);
            val1 *= (tmp1%MOD);
            val2 *= (tmp2%MOD);
            val1 %= MOD;
            val2 %= MOD;
        }
        dp[u][1] = val1;
        dp[u][2] = (val2 - val1 + MOD) % MOD;
    }
}

void solve() {
    // 入力処理
    cin >> N;
    C.resize(N);
    for(ll i=0; i<N; i++) cin >> C[i];
    tree.resize(N);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // 木DP初期化
    dp.resize(N);
    for(ll i=0; i<N; i++) dp[i].resize(3, 0);

    // DFS処理
    dfs(0, -1);
    cout << dp[0][2] << endl;
}


int main() {
    solve();
    return 0;
}