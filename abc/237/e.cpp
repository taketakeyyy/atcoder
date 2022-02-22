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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> Hs(N);
    for (ll i=0; i<N; i++) {
        cin >> Hs[i];
    }

    vector<set<ll>> graph(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    vector<ll> climb(N, INF);  // climb[i] := 広場0から広場iに到達するときの、登った高さの合計の最小値
    climb[0] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> que;  // 小さい順に取り出す
    que.push({0,0});
    while(!que.empty()) {
        ll hsum, u;
        tie(hsum, u) = que.top();
        que.pop();

        for (auto v: graph[u]) {
            if (Hs[u]-Hs[v] < 0) {
                // 登りのとき
                if (climb[v] > (climb[u]+Hs[v]-Hs[u])) {
                    climb[v] = (climb[u]+Hs[v]-Hs[u]);
                    que.push({climb[v], v});
                }
            }
            else {
                // 下りのとき
                if (climb[v] > climb[u]) {
                    climb[v] = climb[u];
                    que.push({climb[v], v});
                }
            }
        }
    }

    // 答え
    ll ans = 0;
    for (ll i=1; i<N; i++) {
        ans = max(ans, Hs[0]-Hs[i] - climb[i]);
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}