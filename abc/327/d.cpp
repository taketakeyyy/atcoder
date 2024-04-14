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


// 二部グラフを作る
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(M), B(M);
    for(ll i=0; i<M; i++) {
        cin >> A[i]; A[i]--;
    }
    for(ll i=0; i<M; i++) {
        cin >> B[i]; B[i]--;
    }
    vector<vector<ll>> G(N); // G[u] := 頂点uに隣接する頂点のリスト
    for(ll i=0; i<M; i++) {
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
    }

    // 二部グラフを作れるか検証する
    vector<ll> X(N, -1);
    bool is_ok = true; // 2部グラフか？
    auto dfs = [&](auto dfs, ll u, ll color) -> void {
        X[u] = color;
        for(ll v: G[u]) {
            if (X[v] == -1) {
                dfs(dfs, v, color^1);
            }
            else if (X[u]==X[v]){
                is_ok = false;
            }
        }
    };
    for(ll u=0; u<N; u++) {
        if (X[u]==-1) dfs(dfs, u, 0);
    }
    if (is_ok) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}