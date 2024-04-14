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
    ll N, Q; cin >> N >> Q;

    map<ll,ll> indeg; // 入次数
    vector<set<ll>> G(N);
    ll ans = N;
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            ll u, v; cin >> u >> v;
            u--; v--;
            if (indeg[u] == 0) ans--;
            if (indeg[v] == 0) ans--;
            indeg[u]++;
            indeg[v]++;
            G[u].insert(v);
            G[v].insert(u);
        }
        else {
            ll u; cin >> u;
            u--;
            if (indeg[u] > 0) {
                for(ll v: G[u]) {
                    indeg[v]--;
                    if (indeg[v] == 0) ans++;
                    G[v].erase(u);
                }
                G[u].clear();
                indeg[u] = 0;
                ans++;
            }
        }
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}