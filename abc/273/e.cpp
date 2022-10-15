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


// 木の構築をイメージする。出力は数列最後の値のみなので、頂点を行き来するだけで良い
// 数列の復元は、親をたどることで可能。だが今回は必要ないので、厳密に木グラフを作る必要はない
void solve() {
    ll Q; cin >> Q;

    map<ll,ll> parent;  // parent[u] := 頂点uの親
    parent[0] = 0;
    map<ll,ll> value;  // value[u] := 頂点uの値
    value[0] = -1;
    ll now_id = 0;  // 現在のノードID
    ll next_id = 1;  // 次に割り振るノードID
    map<ll,ll> page;  // page[y] := ページyにはノードIDを書き込む
    vector<ll> ans;
    for(ll q=0; q<Q; q++) {
        string query; cin >> query;
        if (query == "ADD") {
            ll x; cin >> x;
            parent[next_id] = now_id;
            value[next_id] = x;
            now_id = next_id;
            next_id++;
        }
        if (query == "DELETE") {
            now_id = parent[now_id];
        }
        if (query == "SAVE") {
            ll y; cin >> y;
            page[y] = now_id;
        }
        if (query == "LOAD") {
            ll z; cin >> z;
            now_id = page[z];
        }

        ans.push_back(value[now_id]);
    }

    // 出力
    for(ll i=0; i<(ll)ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}