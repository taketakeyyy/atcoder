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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;

    vector G(N, set<ll>());
    vector<ll> indeg(N, 0);  // 入次数
    for(ll i=0; i<N-1; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].insert(v);
        G[v].insert(u);
        indeg[u]++;
        indeg[v]++;
    }

    // 入次数1の頂点を見つける
    ll tail_u;
    for(ll i=0; i<N; i++) {
        if (indeg[i] == 1) tail_u = i;
    }

    // 二重BFSで探索して、各星のレベルを決定していく
    vector<ll> ans;
    deque<pair<ll,ll>> star_deq; // 各星の探索開始の頂点を管理
    star_deq.push_back({tail_u, 0});
    vector<bool> visited(N, false);
    visited[tail_u] = true;
    while(!star_deq.empty()) {
        auto[start_u, start_cost] = star_deq.front(); star_deq.pop_front();

        deque<pair<ll,ll>> deq; // 星内の頂点をBFSで探索
        deq.push_back({start_u, start_cost});
        ll vnum = 0; // 星の頂点数
        while(!deq.empty()) {
            auto [u, cost] = deq.front(); deq.pop_front();
            vnum++;

            for(ll v: G[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                if (cost+1 >=3) {
                    // 距離が3離れるなら、別の星の頂点
                    star_deq.push_back({v, 0});
                }
                else {
                    // 距離が2以下なら、同じ星内の頂点
                    deq.push_back({v, cost+1});
                }
            }
        }
        ans.push_back(vnum);
    }

    // 出力
    sort(ans.begin(), ans.end());
    for(ll val: ans) {
        cout << val-1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}