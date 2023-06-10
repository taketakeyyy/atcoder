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


// DFSをすればいい。
// 2N回以内で終点を見つけられるか？ -> 最悪ケースの全域木を想定しても必ず探索できる
void solve() {
    ll N, M; cin >> N >> M;

    ll now = 1; // 現在地
    vector<bool> visited(N+1, false);
    visited[now] = true;
    deque<ll> history; // 移動履歴（バックトラック用）
    for(ll t=0; t<2*N; t++) {
        // 入力
        ll K; cin >> K;
        set<ll> vec;
        for(ll i=0; i<K; i++) {
            ll u; cin >> u;
            vec.insert(u);
        }

        // 終了条件
        if (vec.count(N)) {
            cout << N << endl;
            string ok; cin >> ok;
            return;
        }

        // 移動
        bool is_found = false;
        for(ll v: vec) {
            if (visited[v]) continue;
            visited[v] = true;
            is_found = true;
            history.push_back(now);
            cout << v << endl;
            now = v;
            break;
        }
        if (is_found) continue;

        // バックトラック
        ll back_u = history.back(); history.pop_back();
        cout << back_u << endl;
        now = back_u;
    }
}


int main() {
    solve();
    return 0;
}