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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, M; cin >> N >> M;
    vector<vector<pair<ll,ll>>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back({b,c});
        G[b].push_back({a,c});
    }

    // 隣接行列 dist の初期化
    vector dist(N, vector<ll>(N, 0));
    for(int u=0; u<N; u++) {
        for(auto [v, c]: G[u]) {  // G[u] := 頂点uに隣接している頂点リスト
            dist[u][v] = c;  // 頂点uから頂点vへのコスト
        }
    }

    // ワーシャルフロイド実行
    for(int k=0; k<N; k++) {  // 経由する頂点k
        for(int i=0; i<N; i++) {  // 始点i
            for(int j=0; j<N; j++) {  // 終点j
                if (dist[i][j] < dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];  // オーバーフローに注意
                }
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            ans = max(ans, dist[i][j]);
        }
    }
    cout << ans << endl;
}

void solve2() {
    ll N, M; cin >> N >> M;
    vector G(N, vector<ll>(N, -1));
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a][b] = c;
        G[b][a] = c;
    }

    // 全探索
    vector<ll> A(N);
    for(ll i=0; i<N; i++) A[i] = i;
    sort(A.begin(), A.end());
    ll ans = 0;
    do {
        ll total = 0;
        ll u = A[0];
        for(ll i=1; i<N; i++) {
            ll v = A[i];
            if (G[u][v] == -1) {
                continue;
            }
            else {
                total += G[u][v];
                u = A[i];
            }
        }
        ans = max(ans, total);
    }while (next_permutation(A.begin(), A.end()));

    // 答え
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}