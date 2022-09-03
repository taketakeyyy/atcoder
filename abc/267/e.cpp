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


// プライオリティキューを使って、削除するコストが小さい頂点を貪欲に削除するシミュレーションで解く
void solve1() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i];
    }
    vector<set<ll>> G(N+1);
    vector<ll> cost(N+1);  // cost[u] := 頂点uを削除するときのコスト
    for(ll i=1; i<=M; i++) {
        ll u, v; cin >> u >> v;
        G[u].insert(v);
        G[v].insert(u);
        cost[u] += A[v];
        cost[v] += A[u];
    }

    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;  // 小さい順
    for(ll i=1; i<=N; i++) pq.push({cost[i], i});
    vector<bool> deleted(N+1);  // 頂点は削除されているか？
    ll ans = 0;
    while(!pq.empty()) {
        // 頂点uを削除する
        auto[c, u] = pq.top(); pq.pop();
        if (deleted[u]) continue;
        deleted[u] = true;
        ans = max(ans, c);

        // 頂点uと隣接する頂点のコストを更新する
        for(auto v: G[u]) {
            if (deleted[v]) continue;
            cost[v] -= A[u];
            pq.push({cost[v], v});
        }
    }
    cout << ans << endl;
}


// 二分探索用関数
bool f(ll x, ll N, vector<ll> &A, vector<set<ll>> &G, vector<ll> cost) {
    deque<ll> deq;  // 削除する頂点を保持する
    vector<bool> deleted(N+1);
    // set<ll> deleted;  setで保持するとTLEした
    for(ll u=1; u<=N; u++) {
        if (cost[u] <= x) {
            deq.push_back(u);
            deleted[u] = true;
        }
    }

    while(!deq.empty()) {
        ll u = deq.front(); deq.pop_front();

        for(ll v: G[u]) {
            if (deleted[v]) continue;
            cost[v] -= A[u];
            if (cost[v] <= x) {
                deq.push_back(v);
                deleted[v] = true;
            }
        }
    }

    ll cnt = 0;
    for(ll i=1; i<=N; i++) cnt += deleted[i]? 1: 0;
    return (cnt == N);
}

// コストX以下ですべての頂点を削除することができるか？を、Xを二分探索で求める解法
void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i];
    }
    vector<set<ll>> G(N+1);
    vector<ll> cost(N+1);  // cost[u] := 頂点uを削除するときのコスト
    for(ll i=1; i<=M; i++) {
        ll u, v; cin >> u >> v;
        G[u].insert(v);
        G[v].insert(u);
        cost[u] += A[v];
        cost[v] += A[u];
    }

    ll left = 0;
    ll right = 0;
    for(ll i=1; i<=N; i++) right = max(right, cost[i]);
    while(right - left >= 2) {
        ll mid = (right+left)/2;
        if (f(mid, N, A, G, cost)) {
            right = mid;
        }
        else {
            left = mid;
        }
    }
    if (f(left, N, A, G, cost)) {
        cout << left << endl;
    }
    else {
        cout << right << endl;
    }
}


int main() {
    // solve1();
    solve2();
    return 0;
}