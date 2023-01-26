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
// const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


const long long INF = 1000000000;
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];

    // ワーシャルフロイド
    // dist[u][v] := 頂点uから頂点vへの(最短経路,お土産の価値の最大値)
    vector dist(N, vector<pair<ll,ll>>(N, {INF,-1}));
    // distの初期化
    for(ll u=0; u<N; u++) {
        for(ll v=0; v<N; v++) {
            if (S[u][v]=='N') continue;
            dist[u][v] = {1, A[u]+A[v]};
        }
    }
    // ワーシャルフロイド実行
    for(ll k=0; k<N; k++) {  // 経由地点k
        for(ll i=0; i<N; i++) {  // 始点i
            for(ll j=0; j<N; j++) {  // 終点j
                // if (!(S[i][k]=='Y' && S[k][j]=='Y')) continue;  // これ不要！！

                if (dist[i][j].first > dist[i][k].first + dist[k][j].first) {
                    ll ncost = dist[i][k].first + dist[k][j].first;
                    ll nvalue = dist[i][k].second + dist[k][j].second - A[k];
                    dist[i][j] = {ncost, nvalue};
                }
                else if (dist[i][j].first == dist[i][k].first + dist[k][j].first) {
                    // お土産の価値が大きい方を採用
                    ll ncost = dist[i][j].first;
                    ll now_value = dist[i][j].second;
                    ll new_value = dist[i][k].second + dist[k][j].second - A[k];
                    dist[i][j] = {ncost, max(now_value, new_value)};
                }
            }
        }
    }

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        if (dist[u][v].first == INF) {
            cout << "Impossible" << endl;
        }
        else {
            cout << dist[u][v].first << " " << dist[u][v].second << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}