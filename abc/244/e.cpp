#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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


void solve() {
    ll N, M, K, S, T, X; cin >> N >> M >> K >> S >> T >> X;
    vector<set<ll>> G(N+1);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        G[u].insert(v);
        G[v].insert(u);
    }

    // dp[i][j][k] := 頂点iに到達するときの場合の数。ただしjは移動回数。kはXを通った回数の偶奇。
    vector dp(N+1, vector<vector<ll>>(K+1, vector<ll>(2, 0)));
    dp[S][0][0] = 1;
    set<ll> st; st.insert(S);  // 出発する頂点集合
    for(ll j=1; j<=K; j++) {
        set<ll> nxt_st;
        for(ll u: st) {
            for(ll v: G[u]) {
                if (v == X) {
                    dp[v][j][0] += dp[u][j-1][1];
                    dp[v][j][0] %= MOD;
                    dp[v][j][1] += dp[u][j-1][0];
                    dp[v][j][1] %= MOD;
                }
                else {
                    dp[v][j][0] += dp[u][j-1][0];
                    dp[v][j][0] %= MOD;
                    dp[v][j][1] += dp[u][j-1][1];
                    dp[v][j][1] %= MOD;
                }
                nxt_st.insert(v);
            }
        }
        st = nxt_st;
    }

    // 出力
    cout << dp[T][K][0] << endl;
}


int main() {
    solve();
    return 0;
}