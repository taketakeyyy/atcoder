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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// グラフはDAG
// 解説AC
// O(N M^2 logM)
const long long INF = LONG_LONG_MAX - 1001001001001001;
void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N+1); // G[u] := 都市uから到達可能な都市集合
    vector<set<ll>> invG(N+1); // invG[u]: Gの反転グラフ
    for(ll i=1; i<=N; i++) {
        string s; cin >> s;
        for(ll j=1; j<=M; j++) {
            if (s[j-1] == '0') continue;
            G[i].insert(i+j);
            invG[i+j].insert(i);
        }
    }

    // dist1[v] := 都市1から都市vへの最短距離
    vector<ll> dist1(N+1, INF);
    dist1[1] = 0;
    for(ll u=1; u<=N; u++) {
        for(ll v: G[u]) {
            if (dist1[u] == INF) continue;
            dist1[v] = min(dist1[v], dist1[u]+1);
        }
    }

    // distN[v] := 都市Nから都市vへの最短距離
    vector<ll> distN(N+1, INF);
    distN[N] = 0;
    for(ll u=N; u>=1; u--) {
        for(ll v: invG[u]) {
            if (distN[u] == INF) continue;
            distN[v] = min(distN[v], distN[u]+1);
        }
    }

    // 頂点kを通らずに、頂点1から頂点Nへ行けるか？
    for(ll k=2; k<=N-1; k++) { // O(N)
        ll ans = INF;
        // 頂点lから頂点rへ、頂点kを飛び越える O(M^2 logM)
        for(ll l=k-M; l<k; l++) { // kへ伸びる辺は高々M本
            if (l < 1) continue;
            if (dist1[l] == INF) continue;
            for(ll r=k+1; r<=k+M; r++) { // kから伸びる辺は高々M本
                if (r > N || r-l > M) break;
                if (!G[l].count(r)) continue; // lからrへ辺がないならスキップ
                if (distN[r]==INF) continue;
                ans = min(ans, dist1[l]+distN[r]+1);
            }
        }
        if (ans == INF) ans = -1;
        cout << ans << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}