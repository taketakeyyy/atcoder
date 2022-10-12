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
    ll K; cin >> K;
    vector<set<pair<ll,ll>>> G(K);  // G[i] := 頂点iからたどれる頂点集合(コスト, 頂点)
    for(ll i=0; i<K; i++) {
        G[i].insert({1, (i+1)%K});
        G[i].insert({0, (i*10)%K});
    }

    // 頂点1からスタートし、頂点0の最小コストを求める
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;  // 小さい順を維持する優先度付きキュー
    pq.push({0, 1});  // (コスト, 頂点番号)
    vector<ll> cost(K, INF); cost[1] = 0;
    while(!pq.empty()) {
        auto [c, u] = pq.top(); pq.pop();

        for(auto[nc, v]: G[u]) {
            if (cost[v] > c+nc) {
                cost[v] = c+nc;
                pq.push({c+nc, v});
            }
        }
    }

    // 出力
    cout << cost[0]+1 << endl;

}


int main() {
    solve();
    return 0;
}