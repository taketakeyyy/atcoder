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
    ll T; cin >> T;
    for(ll t=0; t<T; t++) {
        ll N, M; cin >> N >> M;
        vector<ll> C(N);
        for(ll i=0; i<N; i++) cin >> C[i];
        vector<set<ll>> G(N);
        for(ll i=0; i<M; i++) {
            ll u, v; cin >> u >> v;
            u--; v--;
            G[u].insert(v);
            G[v].insert(u);
        }

        // BFSで探索する
        // set<pair<ll,ll>> visited; // visitedはsetで持つとTLE!!!!!
        vector visited(N, vector<ll>(N, false));
        deque<tuple<ll,ll,ll>> deq; // (高橋,青木,コスト)
        deq.push_back({0, N-1, 0});
        visited[0][N-1] = true;
        ll ans = -1;
        while(!deq.empty()) {
            auto[taka, aoki, cost] = deq.front(); deq.pop_front();

            if (taka==N-1 && aoki==0) {
                ans = cost; break;
            }

            for(ll nxttaka: G[taka]) {
                for(ll nxtaoki: G[aoki]) {
                    if (visited[nxttaka][nxtaoki]) continue;
                    if (C[nxttaka] == C[nxtaoki]) continue;
                    visited[nxttaka][nxtaoki] = true;
                    deq.push_back({nxttaka, nxtaoki, cost+1});
                }
            }
        }
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}