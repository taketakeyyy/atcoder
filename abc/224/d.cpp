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

vector<set<ll>> G(9);

void solve() {
    ll M; cin >> M;
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].insert(v);
        G[v].insert(u);
    }
    vector<ll>P(8);
    vector<ll>start(9, -1);  // 初期状態
    for(ll i=0; i<8; i++) {
        cin >> P[i];
        P[i]--;
        start[P[i]] = i;
    }

    vector<ll> complete(9, -1);  // 完成形
    for(ll i=0; i<8; i++) complete[i] = i;

    // BFSで答えを探す
    deque<vector<ll>> que;
    que.push_back(start);
    map<vector<ll>,ll> dist;
    dist[start] = 0;
    while(!que.empty()) {
        vector<ll> pos = que.front();
        que.pop_front();

        if (pos == complete) {
            cout << dist[pos] << endl;
            return;
        }

        ll now;
        for(ll i=0; i<9; i++) {
            if (pos[i]==-1) now = i;
        }

        for(ll v: G[now]) {
            vector<ll> npos = pos;
            swap(npos[now], npos[v]);
            if (dist.find(npos) != dist.end()) continue;
            dist[npos] = dist[pos]+1;
            que.push_back(npos);
        }
    }
    cout << -1 << endl;
}


int main() {
    solve();
    return 0;
}