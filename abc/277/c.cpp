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
    ll N; cin >> N;
    map<ll, set<ll>> G;
    for(ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        G[a].insert(b);
        G[b].insert(a);
    }

    ll ans = 1;
    deque<ll> dq; dq.push_back(1);
    set<ll> visited; visited.insert(1);
    while(!dq.empty()) {
        ll u = dq.front(); dq.pop_front();

        for(ll v: G[u]) {
            if (visited.count(v)) continue;
            visited.insert(v);
            ans = max(ans, v);
            dq.push_back(v);
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}