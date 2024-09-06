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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, M, X0; cin >> N >> M >> X0;
    vector<ll> A(M), B(M), S(M), T(M);
    vector<vector<pair<ll,ll>>> G(N);
    for(ll i=0; i<M; i++) {
        cin >> A[i] >> B[i] >> S[i] >> T[i];
        A[i]--; B[i]--;
        G[A[i]].push_back({B[i],i});
    }

    // もともと乗り換え可能な組を探す
    set<pair<ll,ll>> st;
    auto dfs = [&](auto dfs, ll u, ll now_time, ll train_id) -> void {
        for(auto [v, nxt_train_id]: G[u]) {
            if (now_time <= S[nxt_train_id]) {
                st.insert({train_id, nxt_train_id});
                dfs(dfs, v, T[nxt_train_id], nxt_train_id);
            }
        }
    };
    dfs(dfs, B[0], T[0], 0);

    // X[0]の遅延が発生したとして、Xを埋める
    vector<ll> X(M, 0LL);
    X[0] = X0;
    auto dfs2 = [&](auto dfs2, ll u, ll now_time, ll train_id) -> void {
        for(auto[v, nxt_train_id]: G[u]) {
            if (st.count({train_id, nxt_train_id})) {
                // もともと乗り換え可能なので、これも乗れるようにする
                if (now_time > S[nxt_train_id]) {
                    X[nxt_train_id] = now_time - S[nxt_train_id];
                }
                dfs2(dfs2, v, T[nxt_train_id]+X[nxt_train_id], nxt_train_id);
            }
        }
    };
    dfs2(dfs2, B[0], T[0]+X[0], 0);

    // 出力
    for(ll i=1; i<M; i++) {
        cout << X[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}