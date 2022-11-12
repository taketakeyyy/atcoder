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
    vector<vector<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // ソート
    for(ll i=0; i<N; i++) {
        sort(G[i].begin(), G[i].end());
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << (ll)G[i].size() << " ";
        for(ll j=0; j<(ll)G[i].size(); j++) {
            cout << G[i][j]+1 << " ";
        }
        cout << endl;
    }

}


int main() {
    solve();
    return 0;
}