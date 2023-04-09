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
    ll N, K; cin >> N >> K;
    vector<vector<ll>> A(N, vector<ll>(N, 0));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> A[i][j];
        }
    }

    // 隣接行列distの初期化
    vector dist = A;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (dist[i][j] == 0) dist[i][j] = INF;
        }
    }

    // ワーシャルフロイド
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

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll s, t; cin >> s >> t;
        s--; t--;
        s %= N; t %= N;
        cout << ((dist[s][t]==INF) ? -1 : dist[s][t]) << endl;
    }
}


int main() {
    solve();
    return 0;
}