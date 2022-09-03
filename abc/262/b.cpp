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
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].insert(v);
        G[v].insert(u);
    }

    // 全探索
    ll ans = 0;
    for(ll a=0; a<N; a++) {
        for(ll b=a+1; b<N; b++) {
            if (!G[a].count(b)) continue;
            for(ll c=b+1; c<N; c++) {
                if (!G[b].count(c)) continue;
                if (!G[c].count(a)) continue;
                ans++;
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}