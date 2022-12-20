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


// 解説AC
// 「新しく追加できる辺」 = 「すべての辺の場合の数」 - 「新しく追加できない辺」
// 「新しく追加できない辺」 = 「すでに辺が張られている数」 + 「同じ連結成分内の、同じ色同士の辺の組み合わせ」
// 「すでに辺が張られている数」 = M本
// 「同じ連結成分内の、同じ色同士の辺の組み合わせ」 = ある連結成分内のある色がk個なら、C(k,2)通り
// なので、各連結成分ごとに色の個数kを数えて、C(k,2)を計算する。
// 「すべての辺の場合の数」は、C(N,N-1)でOK
void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v; u--; v--;
        G[u].insert(v); G[v].insert(u);
    }

    // 二部グラフを作る
    vector<ll> color(N, -1);  // color[u] := 頂点uの色(0 or 1)
    vector<ll> color_cnt(2);  // 連結成分内の各色のカウント
    auto dfs = [&](auto dfs, ll u, ll c=0) -> bool {
        if (color[u] != -1) {
            return color[u] == c;
        }

        color[u] = c;
        color_cnt[c]++;
        for(ll v: G[u]) {
            if (!dfs(dfs, v, c^1)) return false;
        }
        return true;
    };

    // C(n,2)を計算する
    auto c2 = [](ll n) -> ll {
        return n*(n-1)/2;
    };

    // 「すべての辺の場合の数」から「新しく追加できない辺」を引いていく
    ll ans = c2(N)-M;
    for(ll i=0; i<N; i++) {
        if (color[i] != -1) continue;
        color_cnt = vector<ll>(2);
        if (!dfs(dfs,i)) {
            cout << 0 << endl;
            return;
        }

        // 「新しく追加できない辺」を引く
        for(ll cnt: color_cnt) { ans -= c2(cnt); }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}