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
    vector<vector<ll>> G(N); // G[u] := 本uを読む前に読む必要がある本たち
    vector<ll> outdeg(N); // 出次数
    for(ll i=0; i<N; i++) {
        ll c; cin >> c;
        for(ll j=0; j<c; j++) {
            ll p; cin >> p;
            p--;
            G[i].push_back(p);
            outdeg[i]++;
        }
    }

    vector<ll> ans;
    vector<bool> visited(N, false);
    auto dfs = [&](auto self, ll u) -> void {
        // 終了条件

        // 次の探索
        for(ll v: G[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            self(self, v);
        }
        ans.push_back(u);
        return;
    };

    dfs(dfs, 0);

    for(ll i=0; i<(ll)ans.size()-1; i++) {
        cout << ans[i]+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}