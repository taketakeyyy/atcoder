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


/**
 * @brief 木グラフGの重心を見つける
 * @note 頂点番号は0-indexed
 * @param G G[u] := 頂点uから到達できる頂点のリスト
 * @param W W[u] := 頂点uの重み
 * @return vector<ll> 重心のリスト
 */
vector<ll> find_centroids(const vector<vector<ll>> &G, vector<ll> &W) {
    vector<ll> centroids; // 重心の頂点番号を格納する
    ll totalW = accumulate(W.begin(), W.end(), 0LL);

    // 部分木内の重みの合計を返す
    auto dfs = [&](auto dfs, ll u, ll parent=-1) -> ll {
        ll res = W[u];
        ll mx = 0; // 頂点uから出てる各部分木の重みのmax

        // 次の探索
        for(ll v: G[u]) {
            if (v == parent) continue;
            ll w = dfs(dfs, v, u); // 子方向の部分木の重み
            mx = max(mx, w);
            res += w;
        }
        ll w = totalW-res; // 親方向の部分木の重み
        mx = max(mx, w);
        if (mx*2 <= totalW) centroids.push_back(u); // 重心格納
        return res;
    };
    dfs(dfs,0);

    return centroids;
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N-1), B(N-1);
    vector<vector<ll>> G(N);
    for(ll i=0; i<N-1; i++) {
        cin >> A[i] >> B[i];
        A[i]--; B[i]--;
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
    }
    vector<ll> C(N);
    for(ll i=0; i<N; i++) cin >> C[i];

    // 重心を探す
    auto centroids = find_centroids(G, C);

    // 答え
    ll ans = 0;
    auto dfs2 = [&](auto dfs2, ll u, ll dist=0, ll parent=-1) -> void {
        ans += dist*C[u];
        for(ll v: G[u]) {
            if (v == parent) continue;
            dfs2(dfs2, v, dist+1, u);
        }
    };
    dfs2(dfs2, centroids[0]); // 重心から出発し、距離と重みをかけた答えを計算する
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}