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


void solve() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<ll> W(N), A(N);
    for(ll i=0; i<N; i++) cin >> W[i];
    for(ll i=0; i<N; i++) cin >> A[i];

    // wの値が小さい順にソートする
    vector<pair<ll,ll>> WU(N); // (w,頂点番号)
    for(ll i=0; i<N; i++) WU[i] = {W[i], i};
    sort(WU.begin(), WU.end());

    // dp[u] := 頂点uに1個コマがあるときの、操作回数の最大値
    vector<ll> dp(N, 0LL);
    for(ll i=0; i<N; i++) {
        auto[ignore, u] = WU[i];

        // dp2[w] := 頂点uがw以下の集合を作るときの、得られる操作回数の最大値
        vector<ll> dp2(W[u], 0LL);
        for(ll v: G[u]) {
            if (W[v] >= W[u]) continue;
            for(ll j=W[u]-1; j>=W[v]; j--) {
                chmax(dp2[j], dp2[j-W[v]]+dp[v]);
            }
        }
        dp[u] = dp2[W[u]-1] + 1;
    }

    // 答え
    ll ans = 0;
    for(ll u=0; u<N; u++) ans += A[u]*dp[u];
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}