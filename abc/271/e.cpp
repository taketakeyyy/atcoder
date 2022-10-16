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

// dp[i][v]を、Eのi番目まで見たときの、頂点1から頂点vまでの最短距離とする。
// dp[i][v]を、E[i]のi=1から順に埋めていけば答えは求まるが、これだとMLE、TLEする。
// 実は、辺E[i]に関しては頂点(a,b)に対してのみ更新すればOKなので、vに関してループを回す必要がない。
// よって、以下のようにinplaceで解ける。
//
// dp[v] を、頂点1から頂点iまでの最短距離とする。
// E[i]の、i=1から順にdpを更新することで、Eの部分列によって可能な最短距離が求まる。
void solve() {
    ll N, M, K; cin >> N >> M >> K;
    vector<tuple<ll,ll,ll>> edge(M+1);  // 辺iは、{a,b,c}をつなげている
    for(ll i=1; i<=M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        edge[i] = {a, b, c};
    }
    vector<ll> E(K+1);
    for(ll k=1; k<=K; k++) cin >> E[k];

    // dp[i] := 頂点1から頂点iへの最短距離
    vector<ll> dp(N+1, INF);
    dp[1] = 0;
    for(ll k=1; k<=K; k++) {
        auto[a,b,c] = edge[E[k]];
        if (dp[a] != INF) {
            dp[b] = min(dp[b], dp[a]+c);
        }
    }

    // 出力
    if (dp[N] != INF) cout << dp[N] << endl;
    else cout << -1 << endl;
}

int main() {
    solve();
    return 0;
}