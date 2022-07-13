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


void solve() {
    ll N, M, L; cin >> N >> M >> L;
    vector<vector<pair<ll,ll>>> G(N);
    vector<vector<pair<ll,ll>>> invG(N);  // 反転グラフ
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back({b,c});
        invG[b].push_back({a,c});
    }

    vector dist(N, vector<ll>(M+1, INF));  // dist[i][m] := 頂点iの最短距離。mは道を反転させた数
    priority_queue<tuple<ll,ll,ll,ll>, vector<tuple<ll,ll,ll,ll>>, greater<tuple<ll,ll,ll,ll>>> pq;  // 小さい順を維持する優先度付きキュー
    pq.push({0,0,0,-1});  // {コスト, 反転回数, 頂点番号, 前回の頂点番号}
    while(!pq.empty()) {
        auto[cost, inv_num, u, pre_u] = pq.top(); pq.pop();

        if (dist[u][inv_num] > cost) { continue; }

        // 反転せずに移動
        for(auto [v, c]: G[u]) {
            if (v == pre_u) { continue; }
            ll ncost = cost + c;
            if (ncost > L) { continue; }
            if (dist[v][inv_num] > ncost) {
                dist[v][inv_num] = ncost;
                pq.push({ncost, inv_num, v, u});
            }
        }

        // 反転して移動
        for(auto [v, c]: invG[u]) {
            if (v == pre_u) { continue; }
            ll ncost = cost + c;
            if (ncost > L) { continue; }
            if (dist[v][inv_num+1] > ncost) {
                dist[v][inv_num+1] = ncost;
                pq.push({ncost, inv_num+1, v, u});
            }
        }
    }

}


void solve1() {
    // 拡張0-1BFSの解法 WA わからん
    ll N, M, L; cin >> N >> M >> L;
    vector<vector<pair<ll,ll>>> G(N);
    vector<vector<pair<ll,ll>>> invG(N);  // 反転グラフ
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back({b,c});
        invG[b].push_back({a,c});
    }

    // 拡張0-1BFS
    // dist[i][j] := 頂点iへの{最小反転回数, 累積移動距離}。jはそれまでの反転回数。
    // 同じ頂点に2度訪れるのは明らかに遠回りなので、反転回数は最大N-1回で十分
    vector dist(N, vector<pair<ll,ll>>(N, {-1, 0}));
    dist[0][0] = {0,0};
    deque<tuple<ll,ll,ll>> deq;
    deq.push_back({0,0,0});  // {コスト(反転回数), 累積移動距離, 頂点番号}
    while(!deq.empty()) {
        auto[inv_num, sum_d, u] = deq.front(); deq.pop_front();

        if (u == N-1) { break; }
        if (inv_num >= N) { continue; }

        // 反転せず移動する場合
        for(auto[v, c]: G[u]) {
            if (dist[v][inv_num].first != -1) { continue; }
            if (sum_d+c > L) { continue; }
            dist[v][inv_num] = {inv_num, sum_d+c};
            deq.push_front({inv_num, sum_d+c, v});  // コスト変わらないのでpush_front
        }

        // 反転して移動する場合
        for(auto[v, c]: invG[u]) {
            if (dist[v][inv_num+1].first != -1) { continue; }
            if (sum_d+c > L) { continue; }
            if (inv_num+1 >= N) { continue; }
            dist[v][inv_num+1] = {inv_num+1, sum_d+c};
            deq.push_back({inv_num+1, sum_d+c, v});  // コスト増えるのでpush_back
        }
    }

    // 出力
    ll ans = -1;
    for(ll j=0; j<N; j++) {
        if (dist[N-1][j].first != -1) { ans=j; break; }
    }
    cout << ans << endl;
}


void solve2() {
    // 拡張ダイクストラの解法 AC
    ll N, M, L; cin >> N >> M >> L;
    vector<vector<pair<ll,ll>>> G(N);
    vector<vector<pair<ll,ll>>> invG(N);  // 反転グラフ
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back({b,c});
        invG[b].push_back({a,c});
    }

    // 拡張ダイクストラ
    // dist[i][j] := 頂点iへの最短距離。jはそれまでの反転回数
    // 同じ頂点に2度訪れるのは明らかに遠回りなので、反転回数は最大N-1回で十分
    vector dist(N, vector<ll>(N, INF));
    priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;  // 小さい順を維持する優先度付きキュー
    pq.push({0,0,0});  // {コスト(距離), 反転回数, 頂点番号}
    while(!pq.empty()) {
        auto[cost, inv_num, u] = pq.top(); pq.pop();

        if (dist[u][inv_num] < cost) { continue; }

        // 反転せず移動する場合
        for(auto[v, c]: G[u]) {
            ll ncost = cost + c;
            if (ncost > L) { continue; }
            if (dist[v][inv_num] > ncost) {
                dist[v][inv_num] = ncost;
                pq.push({ncost, inv_num, v});
            }
        }

        // 反転して移動する場合
        for(auto[v, c]: invG[u]) {
            ll ncost = cost + c;
            if (ncost > L) { continue; }
            if (inv_num+1 >= N) { continue; }
            if (dist[v][inv_num+1] > ncost) {
                dist[v][inv_num+1] = ncost;
                pq.push({ncost, inv_num+1, v});
            }
        }
    }

    // 出力
    ll ans = -1;
    for(ll j=0; j<N; j++) {
        if (dist[N-1][j] != INF) { ans=j; break; }
    }
    cout << ans << endl;
}



int main() {
    // solve1();
    solve2();
    return 0;
}