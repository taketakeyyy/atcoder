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


struct Edge {
    ll v, d;
};
/*!!!!!!!!!!!!!!!!!!!!!絶対にダメ!!!!!!!!!!!!!!!!!!!!!*/
// bool operator< (const Edge &e1, const Edge &e2) {
//     return e1.v < e2.v;  // どうでもいい(setに代入するために便宜上必要)
// }
/*!!!!!!!!!!!!!!!!!!!!!絶対にダメ!!!!!!!!!!!!!!!!!!!!!*/

void solve() {
    ll N, M, X; cin >> N >> M >> X;
    vector<ll> T(N);
    for(ll i=0; i<N; i++) {
        cin >> T[i];
    }
    vector<vector<Edge>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b, d; cin >> a >> b >> d;
        a--; b--;
        G[a].push_back({b,d});
        G[b].push_back({a,d});
    }

    // 拡張ダイクストラ。コスト情報を拡張する。
    // dist[i][t][x] := 部屋iへの最短距離
    // tは最後に入った快適でない部屋の温度 t = 0:寒い 1:快適 2:暑い (t=1は使わない)
    // xは最後に入った快適でない部屋からの累積移動距離
    vector dist(N, vector<vector<ll>>(3, vector<ll>(X+1, INF)));
    dist[0][0][0] = 0;
    priority_queue<tuple<ll,ll,ll,ll>, vector<tuple<ll,ll,ll,ll>>, greater<tuple<ll,ll,ll,ll>>> pq;  // 小さい順
    pq.push({0,0,0,0});  // {コスト, 部屋番号, 最後に入った快適でない部屋の温度, 最後に入った快適でない部屋からの累積距離}
    while(!pq.empty()) {
        auto[cost, u, last_t, sum_d] = pq.top(); pq.pop();

        if (dist[u][last_t][sum_d] < cost) { continue; }

        for(const auto &e: G[u]) {
            ll ncost = cost + e.d;
            if (T[e.v] == 0) {
                // 行き先の部屋が寒すぎならば
                if ((last_t==2) && (sum_d+e.d < X)) { continue; }
                if (dist[e.v][last_t][min(sum_d+e.d, X)] > ncost) {
                    dist[e.v][last_t][min(sum_d+e.d, X)] = ncost;
                    pq.push({ncost, e.v, 0, 0});
                }
            }
            else if (T[e.v] == 2) {
                // 行き先の部屋が暑すぎならば
                if ((last_t==0) && (sum_d+e.d < X)) { continue; }
                if (dist[e.v][last_t][min(sum_d+e.d, X)] > ncost) {
                    dist[e.v][last_t][min(sum_d+e.d, X)] = ncost;
                    pq.push({ncost, e.v, 2, 0});
                }
            }
            else {
                // 行き先の部屋が快適ならば ok
                if (dist[e.v][last_t][min(sum_d+e.d, X)] > ncost) {
                    dist[e.v][last_t][min(sum_d+e.d, X)] = ncost;
                    pq.push({ncost, e.v, last_t, min(sum_d+e.d, X)});
                }
            }
        }
    }

    ll ans = INF;
    for(ll x=0; x<=X; x++) {
        ans = min(ans, min(dist[N-1][0][x], dist[N-1][2][x]));
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}