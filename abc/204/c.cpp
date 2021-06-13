#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> paths(N);
    for(int i=0; i<M; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        paths[a].push_back(b);
    }

    ll ans = 0;
    for(int i=0; i<N; i++) {
        set<ll> visited;
        deque<ll> que;
        visited.insert(i);
        que.push_back(i);
        ans++;

        while (que.size() != 0) {
            ll u = que.front(); que.pop_front();
            for(auto v: paths[u]) {
                if (visited.count(v)) continue;
                visited.insert(v);
                ans++;
                que.push_back(v);
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}