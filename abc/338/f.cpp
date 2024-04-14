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
    vector G(N, vector(0, make_pair<ll,ll>(0,0)));
    for(ll i=0; i<M; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        G[u].push_back({v,w});
    }

    // dist[u][v] := 頂点uから頂点vへの最短距離
    vector dist(N, vector(N, INF));
    for(ll u=0; u<N; u++) {
        dist[u][u] = 0;
        for(auto[v, w]: G[u]) {
            dist[u][v] = w;
        }
    }
    // ワーシャルフロイド
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][k]==INF or dist[k][j]==INF) continue;
                if (dist[i][j] > dist[i][k]+dist[k][j]) {
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
            }
        }
    }

    // bitDP
    // dp[i][S] := 現在地が頂点iで、訪問済みの頂点の集合がSのときの、コストの最小値
    vector dp(N, vector(1<<N, INF));
    // dp初期化
    for(ll s=0; s<N; s++) { // 始点sから始めるとき
        dp[s][1LL<<s] = 0;
    }

    // bitDP
    for(ll bit=0; bit<1<<N; bit++) {
        for(ll i=0; i<N; i++) { // 現在の頂点i
            if (dp[i][bit]==INF) continue;
            if (~bit>>i&1) continue; // iはまだ訪れていない
            for(ll j=0; j<N; j++) { // 次に訪れる頂点j
                if (bit>>j&1) continue; // すでに訪れている
                if (dist[i][j]==INF) continue; // そもそもiからjへ行けない
                chmin(dp[j][bit|(1LL<<j)], dp[i][bit]+dist[i][j]);
            }
        }
    }

    // 答え
    ll ans = INF;
    for(ll i=0; i<N; i++) chmin(ans, dp[i][(1<<N)-1]);
    if (ans == INF) cout << "No" << endl;
    else cout << ans << endl;
}


int main() {
    solve();
    return 0;
}