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


void solve() {
    ll N, M, R; cin >> N >> M >> R;
    vector<ll> city(R);
    for(ll i=0; i<R; i++) {
        cin >> city[i]; city[i]--;
    }
    vector<map<ll,ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a][b] = c;
        G[b][a] = c;
    }

    // ワーシャルフロイドで全頂点最短距離を求める
    // 隣接行列を作成
    vector<vector<ll>> dist(N, vector<ll>(N, INF));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (i == j) dist[i][j] = 0;
            if (G[i].count(j)) dist[i][j] = G[i][j];
        }
    }

    // ワーシャルフロイド実行
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][k]==INF || dist[k][j]==INF) continue;
                if (dist[i][j] > dist[i][k]+dist[k][j]) {
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
            }
        }
    }

    // R個の街の順列の行き方を最大8!(=40320)通り試す
    ll ans = INF;
    sort(city.begin(), city.end());
    do {
        ll u = city[0];
        ll total = 0;
        for(ll i=1; i<R; i++) {
            ll v = city[i];
            total += dist[u][v];
            u = v;
        }
        ans = min(ans, total);
    }while(next_permutation(city.begin(), city.end()));
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}