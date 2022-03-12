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
const long long INF = 10000000000000;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N, M; cin >> N >> M;
    vector<set<pair<ll,ll>>> G(N);
    vector<vector<ll>> dist(N, vector<ll>(N, INF));
    set<pair<ll,ll>> edge_set;
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a].insert({b,c});
        G[b].insert({a,c});

        dist[a][b] = c;
        dist[b][a] = c;

        edge_set.insert({min(a,b), max(a,b)});
    }

    // ワーシャルフロイド
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][j] > dist[i][k]+dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 削除しても良い辺は、隣接している辺の癖に、最短距離じゃないやつ
    // もう一度ワーシャルフロイドで、迂回してもＯＫなやつは隣接辺を消せるやつを探す
    ll ans = 0;
    set<pair<ll,ll>> visited;
    for(ll i=0; i<N; i++) {
        for(ll j=i+1; j<N; j++) {
            for(ll k=0; k<N; k++) {
                if (dist[i][j] == dist[i][k]+dist[k][j]) {
                    if (edge_set.count({i,j})) {
                        if (!visited.count({i,j})) {
                            ans++;
                            visited.insert({i,j});
                        }
                    }
                }
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}