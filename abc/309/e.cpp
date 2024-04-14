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
    vector<ll> P(N+1, -1);
    for(ll i=2; i<=N; i++) cin >> P[i];
    vector<set<ll>> G(N+1); // 子孫を下っていくグラフ
    for(ll i=2; i<=N; i++) {
        G[P[i]].insert(i);
    }

    // 一番上の人間は誰？
    ll root = 1; // 一番上の人
    while(1) {
        if (P[root] == -1) break;
        root = P[root];
    }

    vector<ll> target(N+1, -1); // target[i] := 人iは保険対象者か？対象者でないなら-1。対象者なら最大何代先まで対象者なのか
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        target[x] = max(target[x], y); // 複数保険に入っている人がいることに注意
    }

    // 一番上の人から1代ずつ下っていって処理する O(N)
    deque<ll> deq;
    deq.push_back(root);
    while(!deq.empty()) {
        ll u = deq.front(); deq.pop_front();

        // 高々合計N回
        for(ll v: G[u]) {
            target[v] = max(target[v], target[u]-1);
            deq.push_back(v);
        }
    }

    // 答え
    ll ans = 0;
    for(ll i=1; i<=N; i++) {
        if (target[i] >= 0) ans++;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}