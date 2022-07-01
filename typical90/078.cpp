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
    vector<set<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].insert(b);
        G[b].insert(a);
    }

    // 自分自身より頂点番号が小さい隣接頂点がちょうど１つ存在するか数える
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ll cnt = 0;
        for(auto v: G[i]) {
            if (v < i) { cnt++; }
        }
        if (cnt == 1) { ans++; }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}