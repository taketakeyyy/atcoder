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

class WarshallFloyd {
    /***ワーシャルフロイド法
     * 計算量:
     *   O(V**3)
    ***/
    vector<vector<long long>> dist;  // 隣接行列dist[i][j]:=iからjへ行くまでのコスト
    long long v;  // 頂点数

    public:
        WarshallFloyd(long long n) {
            /***
             * Args:
             *  n(long long): 頂点数
             **/
            this->dist.resize(n);
            for (long long i=0; i<n; i++) {
                this->dist[i].resize(n, LONG_LONG_MAX);
            }
            for (long long i=0; i<n; i++) {
                this->dist[i][i] = 0;
            }
            this->v = n;
        }

        long long get_vertex_num() {
            // 頂点数を返す
            return this->v;
        }

        void update(long long u, long long v, long long cost) {
            /*** 隣接行列のコストを更新する
             * Args:
             *   u(long long): 頂点uから
             *   v(long long): 頂点vへの
             *   cost(long long): コストをcostに更新する
             **/
            // 二重辺に注意
            this->dist[u][v] = min(this->dist[u][v], cost);
        }

        vector<vector<long long>> shortest_path() {
            /* 最短距離を計算する */
            for (long long k=0; k<this->v; k++) {
                for (long long i=0; i<this->v; i++) {
                    for (long long j=0; j<this->v; j++) {
                        long long ncost = this->dist[i][k]+this->dist[k][j]; if (dist[i][k]>0 && dist[k][j]>0 && ncost < 0) ncost = LONG_LONG_MAX;  // オーバーフロー対策（オーバーフローしたらLONG_LONG_MAXにする）
                        this->dist[i][j] = min(this->dist[i][j], ncost);
                    }
                }
            }
            return this->dist;
        }
};

void solve() {
    ll N, M; cin >> N >> M;
    // ワーシャルフロイドで全頂点対の最短距離を求めておく
    WarshallFloyd ws(N);
    vector<tuple<ll,ll,ll>> bridge(M);
    for(ll i=0; i<M; i++) {
        ll u, v, t; cin >> u >> v >> t;
        u--; v--;
        ws.update(u, v, t);
        ws.update(v, u, t);
        bridge[i] = {u,v,t};
    }
    auto dist = ws.shortest_path();

    // クエリ処理
    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll K; cin >> K;
        vector<ll> B(K);
        for(ll k=0; k<K; k++) {
            cin >> B[k];
            B[k]--;
        }

        // 橋のわたる順番を全探索
        ll ans = INF;
        sort(B.begin(), B.end());
        do {
            // dp[0] := 頂点uにいるときの最短距離
            // dp[1] := 頂点vにいるときの最短距離
            vector<ll> dp(2, 0LL);
            ll nowU = 0, nowV = 0;
            for(ll k=0; k<K; k++) {
                auto[u, v, t] = bridge[B[k]];

                vector<ll> nxtdp(2, INF);
                // nowU -> v -> u のわたり方
                chmin(nxtdp[0], dp[0]+dist[nowU][v]+t);
                // nowV -> v -> u のわたり方
                chmin(nxtdp[0], dp[1]+dist[nowV][v]+t);
                // nowU -> u -> v のわたり方
                chmin(nxtdp[1], dp[0]+dist[nowU][u]+t);
                // nowV -> u -> v のわたり方
                chmin(nxtdp[1], dp[1]+dist[nowV][u]+t);
                nowU = u;
                nowV = v;
                swap(nxtdp, dp);
            }
            // 最後、N-1に向かう
            ll res = INF;
            chmin(res, dp[0]+dist[nowU][N-1]);
            chmin(res, dp[1]+dist[nowV][N-1]);
            chmin(ans, res);
        }while (next_permutation(B.begin(), B.end()));
        // 出力
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}