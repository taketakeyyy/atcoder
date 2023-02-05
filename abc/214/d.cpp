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


class UnionFindVerSize {
    private:
        vector<ll> parents; // 頂点uの親
        vector<ll> sizes; // 頂点uが所属するグループのサイズ
        ll group_num;  // グループ数
    public:
        UnionFindVerSize(ll N) {
            parents.resize(N);
            for(ll i=0; i<N; i++) parents[i] = i;
            sizes.resize(N,1);
            group_num = N;
        }

        // 頂点uのroot（代表）を返す
        ll find_root(ll u) {
            if (parents[u] == u) return u;
            parents[u] = find_root(parents[u]); // 縮約
            return parents[u];
        }

        // 頂点uと頂点vを合併する
        void unite(ll u, ll v) {
            ll ru = find_root(u);
            ll rv = find_root(v);
            if (ru == rv) return;

            if (sizes[ru] < sizes[rv]) {
                parents[ru] = rv;
                sizes[rv] += sizes[ru];
            }
            else {
                parents[rv] = ru;
                sizes[ru] += sizes[rv];
            }
            group_num--;
        }

        // 頂点uが所属するグループのサイズを返す
        ll get_size(ll u) {
            return sizes[find_root(u)];
        }
};


void solve() {
    ll N; cin >> N;

    // 辺のコストが小さい順に貪欲に合併していくと、その辺がfの答えになる個数を数えられる
    vector<tuple<ll,ll,ll>> edges;  // (コスト, 頂点u, 頂点v)
    for(ll i=0; i<N-1; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        edges.push_back({w,u,v});
    }
    sort(edges.begin(), edges.end());

    // コストが小さい辺を貪欲に合併させていく
    ll ans = 0;
    UnionFindVerSize uf(N);
    for(ll i=0; i<(ll)edges.size(); i++) {
        auto[w,u,v] = edges[i];
        ll cnt = uf.get_size(u) * uf.get_size(v);
        ans += w *cnt;
        uf.unite(u,v);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}