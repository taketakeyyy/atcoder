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
    ll N, A, B, C; cin >> N >> A >> B >> C;
    vector D(N, vector<ll>(N));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) cin >> D[i][j];
    }

    vector dist(N, vector<ll>(2, 0)); // dist[j][k] := 都市0から各都市jへの、車から降りた（k=0 or 1)のときの、最短距離
    for(ll i=1; i<N; i++) {
        dist[i][0] = D[0][i]*A; // 車移動
        dist[i][1] = D[0][i]*B+C; // 電車移動
    }
    for(ll i=0; i<N; i++) { // 出発地点
        for(ll j=0; j<N; j++) { // 目的地
            dist[j][0] = min(dist[j][0], dist[i][0]+D[i][j]*A);
            dist[j][1] = min(dist[j][1], dist[i][0]+D[i][j]*B+C);
            dist[j][1] = min(dist[j][1], dist[i][1]+D[i][j]*B+C);
        }
    }
    //出力
    ll ans = min(dist[N-1][0], dist[N-1][1]);
    cout << ans << endl;
}

// これなんで駄目なん？（入力例1で検証）
void solve2() {
    ll N, A, B, C; cin >> N >> A >> B >> C;
    vector D(N, vector<ll>(N));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) cin >> D[i][j];
    }

    vector dist(N, vector<ll>(2, 0)); // dist[i][k] := 都市0から各都市iへの、車から降りた（k=0 or 1)のときの、最短距離
    for(ll i=1; i<N; i++) {
        dist[i][0] = D[0][i]*A; // 車移動
        dist[i][1] = D[0][i]*B+C; // 電車移動
    }

    // ダイクストラ法
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;  // 小さい順を維持する優先度付きキュー
    pq.push({0,0,0}); // (コスト, 頂点, 車から降りたか)
    while(!pq.empty()) {
        auto [cost, u, is_car] = pq.top(); pq.pop();

        // スキップ処理
        if (dist[u][is_car] < cost) continue;

        // 隣接頂点の更新処理
        for(ll v=0; v<N; v++) {
            if (u == v) continue;

            if (is_car == 0) {
                // 車で移動中
                if (dist[v][0] > dist[u][0]+D[u][v]*A) { // 車 -> 車
                    dist[v][0] = dist[u][0]+D[u][v]*A;
                    pq.push({dist[v][0], v, 0});
                }
                if (dist[v][1] > dist[u][0]+D[u][v]*B+C) { // 車 -> 電車
                    dist[v][1] = dist[u][0]+D[u][v]*B+C;
                    pq.push({dist[v][1], v, 1});
                }
            }
            else {
                // 電車で移動中
                if (dist[v][1] > dist[u][1]+D[u][v]*B+C) { // 電車 -> 電車
                    dist[v][1] = dist[u][1]+D[u][v]*B+C;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    //出力
    ll ans = min(dist[N-1][0], dist[N-1][1]);
    cout << ans << endl;
}

// 両側探索
// ・都市1から各都市まで車で移動するときの最短距離
// ・都市Nから各都市まで電車で移動するときの最短距離
// 上記2つを組み合わせて最短距離を探す
void solve3() {
    ll N, A, B, C; cin >> N >> A >> B >> C;
    vector D(N, vector<ll>(N));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) cin >> D[i][j];
    }

    // ダイクストラ法
    auto dijkstra = [&](ll s, bool is_car) {
        vector<ll> dist(N, INF);
        dist[s] = 0;
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<>> pq;  // 小さい順を維持する優先度付きキュー
        pq.push({0,s}); // (コスト,都市)
        while(!pq.empty()) {
            auto[cost, u] = pq.top(); pq.pop();

            if (dist[u] < cost) continue;

            for(ll v=0; v<N; v++) {
                if(v == u) continue;
                ll ncost;
                if (is_car) ncost = cost + D[u][v]*A;
                else ncost = cost + D[u][v]*B+C;
                if (dist[v] > ncost) {
                    dist[v] = ncost;
                    pq.push({ncost,v});
                }
            }
        }
        return dist;
    };
    auto distA = dijkstra(0, true); // distA[i] := 都市0から都市iまで車で移動するときの最短距離
    auto distB = dijkstra(N-1, false); // distB[i] := 都市N-1から都市iまで電車で移動するときの最短距離

    // 都市uで車から電車に乗り換えるときを探索する
    ll ans = INF;
    for(ll u=0; u<N; u++) {
        ans = min(ans, distA[u] + distB[u]);
    }
    cout << ans << endl;
}

int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}