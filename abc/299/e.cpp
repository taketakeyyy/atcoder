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


// 各kについて、距離がd未満の頂点は必ず白に塗らなくてはならない
// 白色に塗る制約が強くて、黒色に塗る制約は弱め。
// 白色に塗らなかった頂点は全部黒に塗ってかまわない？
// 色を塗ったあと、矛盾がないか検証する
void solve() {
    ll N, M; cin >> N >> M;
    vector<set<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].insert(v);
        G[v].insert(u);
    }

    // 仮の答えansを作成する
    // 黒 から 白 への上書きOK
    // 白 から 黒 への上書きはだめ
    ll K; cin >> K;
    vector<ll> ans(N, -1);
    vector<ll> P(K), D(K);
    for(ll k=0; k<K; k++) {
        ll p, d; cin >> p >> d;
        p--;
        P[k] = p; D[k] = d;

        // BFS
        deque<pair<ll,ll>> deq; deq.push_back({p,0});
        vector<ll> visited(N, false);
        visited[p] = true;
        while(!deq.empty()) {
            auto[u, cost] = deq.front(); deq.pop_front();

            if (cost == d) {
                if (ans[u] == -1) ans[u] = 1; // 未確定なら黒にする
                continue;
            }
            ans[u] = 0; // 道中は必ず白にする

            if (cost < d) {
                for(ll v: G[u]) {
                    if (visited[v]) continue;
                    visited[v] = true;
                    deq.push_back({v, cost+1});
                }
            }
        }
    }

    // 作成したansを検証する
    for(ll k=0; k<K; k++) {
        ll p = P[k];
        ll d = D[k];

        // BFS
        deque<pair<ll,ll>> deq; deq.push_back({p,0});
        vector<ll> visited(N, false);
        visited[p] = true;
        bool is_ok = false; // 最小距離がdか？
        while(!deq.empty()) {
            auto[u, cost] = deq.front(); deq.pop_front();

            if (cost == d) {
                if (ans[u] == 1) is_ok = true;
                continue;
            }

            // 矛盾が起きている
            if (ans[u] == 1) {
                is_ok = false;
                break;
            }

            if (cost < d) {
                for(ll v: G[u]) {
                    if (visited[v]) continue;
                    visited[v] = true;
                    deq.push_back({v, cost+1});
                }
            }
        }

        if(!is_ok) {
            cout << "No" << endl;
            return;
        }
    }

    // 1個以上の黒がないとだめ。未確定の箇所(-1)があるならそこを黒にする
    for(ll i=0; i<N; i++) {
        if (ans[i] == -1) ans[i] = 1;
    }

    // 検証の結果、OKだった。
    cout << "Yes" << endl;
    for(ll i=0; i<N; i++) {
        if (ans[i] == -1) cout << 0;
        else cout << ans[i];
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}