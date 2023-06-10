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
    ll N, M, K; cin >> N >> M >> K;
    vector<set<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G[a].insert(b);
        G[b].insert(a);
    }

    // プライオリティキューで体力が大きい順に処理する
    priority_queue<pair<ll,ll>> pq;  // (体力, 頂点) 大きい順を維持する優先度付きキュー
    set<ll> ans;
    vector<ll> visited(N, -1); // visited[u] := 頂点uに到達したときの警備員の体力
    for(ll i=0; i<K; i++) {
        ll p, h; cin >> p >> h;
        p--;
        pq.push({h,p});
        visited[p] = max(visited[p], h);
        ans.insert(p);
    }

    // 体力が大きい順に、警備員を移動しながら処理
    while(!pq.empty()) {
        auto[hp, u] = pq.top(); pq.pop();
        if (visited[u] > hp) continue; // 頂点に書かれている体力より低い体力のとき、もう役に立たない

        // コスト1払って移動する
        for(ll v: G[u]) {
            if (visited[v] >= hp-1) continue;
            visited[v] = hp-1;
            ans.insert(v);
            if (hp-1 >= 1) pq.push({hp-1, v});
        }
    }

    // 出力
    cout << ans.size() << endl;
    for(ll v: ans) {
        cout << v+1 << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}