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
    ll N, M; cin >> N >> M;
    vector<vector<tuple<ll,ll,ll>>> G(N); // 人iから見て(人, x, y);
    for(ll i=0; i<M; i++) {
        ll a, b, x, y; cin >> a >> b >> x >> y;
        a--; b--;
        G[a].push_back({b,x,y});
        G[b].push_back({a,-x,-y});
    }

    // 人の位置
    vector<pair<ll,ll>> coords(N);
    coords[0] = {0,0};

    // BFS
    deque<ll> deq; // 次に見る人
    deq.push_back(0);
    vector<bool> visited(N, false);
    visited[0] = true;
    vector<bool> fix(N, false); // 位置が確定した人
    fix[0] = true;
    while(!deq.empty()) {
        ll u = deq.front(); deq.pop_front();

        for(auto[v, x, y]: G[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            fix[v] = true;
            ll v_x = coords[u].first + x;
            ll v_y = coords[u].second + y;
            coords[v] = {v_x, v_y};
            deq.push_back(v);
        }
    }

    // 答え
    for(ll i=0; i<N; i++) {
        if (fix[i]) {
            cout << coords[i].first << " " << coords[i].second << endl;
        }
        else {
            cout << "undecidable" << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}