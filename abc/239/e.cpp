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


// AC
// Kが小さいので、各頂点を根としたときの部分木の上位20個持たせてもO(NKlog(NK))くらいでいけそう
void solve() {
    ll N, Q; cin >> N >> Q;
    vector<ll> X(N);
    for(ll i=0; i<N; i++) cin >> X[i];

    // 木構造Tを作る
    vector<vector<ll>> T(N);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        T[a].push_back(b);
        T[b].push_back(a);
    }

    // DFSで葉から順にranking[i]を求めていく
    vector<vector<ll>> ranking(N); // ranking[i] := 頂点iを根とする部分木の上位20個の値を保持
    auto dfs = [&](auto self, ll u, ll parent) -> void {
        // 子vを探索
        for(ll v: T[u]) {
            if (v == parent) continue;
            self(self, v, u);

            // 子vの上位20個を貰う
            for(ll val: ranking[v]) {
                ranking[u].push_back(val);
            }
        }

        // 頂点uを根とする部分木の上位20個までをソートして求める
        ranking[u].push_back(X[u]);
        sort(ranking[u].begin(), ranking[u].end());
        reverse(ranking[u].begin(), ranking[u].end());
        ranking[u].resize(20);
    };
    dfs(dfs, 0, -1);

    //クエリ処理
    for(ll q=0; q<Q; q++) {
        ll v, k; cin >> v >> k;
        v--; k--;
        cout << ranking[v][k] << endl;
    }
}

int main() {
    solve();
    return 0;
}