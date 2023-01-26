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


const long long INF = 1e6 * 401;

// f(s,t,k) := s,t,およびk以下の頂点を使ったときの(s,t)の最短距離
// とは、k-1以下の頂点を使って(s,k)まで行き、k-1以下の頂点を使って(k,t)へ行ったときの最短距離である。
// よって、以下の漸化式が成り立つ。
// f(s,t,k) = min(f(s,t,k-1), f(s,k,k-1) + f(k,t,k-1))
//
// f(s,t,k) を求めるにあたって、
// ・頂点kを使わないとき
//   f(s,t,k) = f(s,t,k-1)
// ・頂点kを使うとき
//   f(s,t,k) = f(s,k,k-1) + f(k,t,k-1)
// 動的計画法っぽく書けば良い
// ...のだが、うまくかけなかった。WAが出る。
// ワーシャルフロイド
void solve() {
    ll N, M; cin >> N >> M;
    // G[u] := 頂点uから行ける頂点リストで、(頂点,コスト)
    vector<vector<pair<ll,ll>>> G(N);
    for(ll i=0; i<M; i++) {
        ll a,b,c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back({b,c});
    }

    // ワーシャルフロイドdist初期化
    // dist[i][j][k] := f(i,j,k) := s,t,およびk以下の頂点を使ったときの(s,t)の最短距離
    vector dist(N, vector<vector<ll>>(N, vector<ll>(N, INF)));
    for(ll i=0; i<N; i++) {
        for(ll k=0; k<N; k++) {
            for(auto[j, cost]: G[i]) {
                dist[i][j][k] = cost;
            }
            dist[i][i][k] = 0;
        }
    }

    // ワーシャルフロイド実行
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                // こっちが正しい
                if (dist[i][j][k] > dist[i][k][k] + dist[k][j][k]) {
                    dist[i][j][k] = dist[i][k][k] + dist[k][j][k];
                }

                // こっちはだめ（なんで？）
                // if (k-1>=0 && dist[i][j][k] > dist[i][k][k-1] + dist[k][j][k-1]) {
                //     dist[i][j][k] = dist[i][k][k-1] + dist[k][j][k-1];
                // }

                if (k-1>=0) {
                    dist[i][j][k] = min(dist[i][j][k], dist[i][j][k-1]);
                }
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][j][k] != INF) ans += dist[i][j][k];
            }
        }
    }
    cout << ans << endl;
}

// 普通のワーシャルフロイドで解く。
// ワーシャルフロイドは以下の形をしている。
// for(ll k=0; k<N; k++) {  // 経由地点
//   for(ll i=0; i<N; i++) {  // 始点
//      for(ll j=0; j<N; j++) {  // 終点
//        if (dist[i][j] > dist[i][k]+dist[k][j]) {
//          // dist[i][j]の最短距離を更新
// このようなループの形で、kを経由するときの最短距離dist[i][j]を求めるということの意味は、
// 頂点k以下を使ったときのiからjへの最短距離を求めたこととイコールである。
// こっちはACする。
void solve2() {
    ll N, M; cin >> N >> M;
    // G[u] := 頂点uから行ける頂点リストで、(頂点,コスト)
    vector<vector<pair<ll,ll>>> G(N);
    for(ll i=0; i<M; i++) {
        ll a,b,c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back({b,c});
    }

    // ワーシャルフロイドdist初期化
    vector dist(N, vector<ll>(N, INF));
    for(ll i=0; i<N; i++) {
        for(auto[j, cost]: G[i]) {
            dist[i][j] = cost;
        }
        dist[i][i] = 0;
    }

    // ワーシャルフロイド実行
    ll ans = 0;
    for(ll k=0; k<N; k++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (dist[i][j] > dist[i][k]+dist[k][j]) {
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
                if (dist[i][j] != INF) ans += dist[i][j];
            }
        }
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}