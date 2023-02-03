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


// 高橋と青木の間にある街の数が奇数か偶数か？
void solve() {
    ll N, Q; cin >> N >> Q;
    vector<set<ll>> G(N);
    for(ll i=0; i<N-1; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].insert(b);
        G[b].insert(a);
    }

    // まず街の端っこを求めたい。
    // 適当な頂点を始点として、最も遠い頂点が街の端っこ
    ll root;  // 街の端っこの頂点番号
    {
        deque<pair<ll,ll>> deq;
        deq.push_back({0,0});  // (頂点番号,コスト)
        vector<bool> visited(N, false);
        visited[0] = true;
        ll root_cost = 0;
        while(!deq.empty()) {
            auto[u, cost] = deq.front(); deq.pop_front();
            for(ll v: G[u]) {
                if (visited[v]) continue;
                deq.push_back({v, cost+1});
                visited[v] = true;
                if (root_cost < cost+1) {
                    root_cost = cost+1;
                    root = v;
                }
            }
        }
    }

    // 各頂点の、街の端っこからの距離を求める
    vector<ll> from_root(N, -1);  // 各頂点は、街の端っこからどのくらい離れているか？
    map<ll,ll> vertex2idx; // 頂点番号を累積和用のインデックスに変換
    {
        from_root[root] = 0;
        deque<pair<ll,ll>> deq; deq.push_back({root,0});  // (頂点番号,コスト)
        while(!deq.empty()) {
            auto[u, cost] = deq.front(); deq.pop_front();

            for(ll v: G[u]) {
                if (from_root[v] != -1) continue;
                from_root[v] = cost+1;
                deq.push_back({v, cost+1});
            }
        }
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll c, d; cin >> c >> d;
        c--; d--;
        ll dist = abs(from_root[c] - from_root[d]);
        if (dist%2 == 0) cout << "Town" << endl;
        else cout << "Road" << endl;
    }
}


int main() {
    solve();
    return 0;
}