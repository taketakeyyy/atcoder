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


// 辺iを封鎖したとき、頂点uから頂点vへ移動する際に左回りするか右回りするかは一意に決まる
// 辺iを封鎖したときの移動コストをいもす法で求める
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> X(M);
    for(ll i=0; i<M; i++) {
        cin >> X[i];
        X[i]--;
    }

    // imos[i] := 辺iを封鎖したときの移動距離をいもす法で求める
    vector<ll> imos(N+1, 0);
    for(ll i=1; i<M; i++) {
        ll u = X[i-1]; // 移動元
        ll v = X[i]; // 移動先
        if (v < u) swap(u,v);

        ll rcnt = v-u; // 右回りの長さ
        ll lcnt = u+(N-v); // 左回りの長さ

        // 左回りするしかないとき
        imos[u] += lcnt;
        imos[v] -= lcnt;

        // 右回りするしかないとき
        imos[0] += rcnt;
        imos[u] -= rcnt;
        imos[v] += rcnt;
        imos[N] -= rcnt;
    }
    for(ll i=1; i<N+1; i++) {
        imos[i] = imos[i] + imos[i-1];
    }

    // 最小値は？
    ll ans = INF;
    for(ll i=0; i<N; i++) {
        chmin(ans, imos[i]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}