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

ll N, M, K;
vector<vector<pair<ll,ll>>> G;
vector<bool> exist_switch;


void solve() {
    cin >> N >> M >> K;
    G.resize(N+1);

    for(ll i=0; i<M; i++) {
        ll u, v, a; cin >> u >> v >> a;
        G[u].push_back({v,a});
        G[v].push_back({u,a});
    }

    exist_switch.resize(N+1, false);
    for(ll i=0; i<K; i++) {
        ll s; cin >> s;
        exist_switch[s] = true;
    }

    // BFS
    deque<tuple<ll,ll,ll>> deq;  // {頂点番号, スイッチ状態(0 or 1), 移動回数}
    deq.push_back({1, 0, 0});
    vector<set<ll>> visited(2);
    visited[0].insert(1);
    while(!deq.empty()) {
        auto[u, state, cost] = deq.front(); deq.pop_front();

        if (u == N) {
            cout << cost << endl;
            return;
        }

        for(auto[v, a]: G[u]) {
            if (a^state==1 && !visited[state].count(v)) {
                visited[state].insert(v);
                deq.push_back({v, state, cost+1});
            }

            // スイッチを押す場合
            if (exist_switch[u]) {
                ll nstate = state^1;
                if (a^nstate==1 && !visited[nstate].count(v)) {
                    visited[nstate].insert(v);
                    deq.push_back({v, nstate, cost+1});
                }
            }
        }
    }
    cout << -1 << endl;
}


int main() {
    solve();
    return 0;
}