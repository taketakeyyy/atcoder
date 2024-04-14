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


struct Edge {
public:
    ll l, d, k, c;
};

void solve() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> G(N), invG(N);
    map<pair<ll,ll>, Edge> edges;
    for(ll i=0; i<M; i++) {
        ll l, d, k, c, a, b;
        cin >> l >> d >> k >> c >> a >> b;
        a--; b--;
        G[a].push_back(b);
        invG[b].push_back(a);
        edges[{a,b}] = Edge{l,d,k,c};
    }

    // 二分探索用関数。x番目の電車で出発することができるか？
    auto f = [&](ll x, ll target_time, const Edge &edge) {
        ll t = edge.l + x*edge.d; // x番目の電車で出発するときの時刻
        return t <= target_time;
    };

    // 頂点Nからダイクストラ的に、最も遅い出発時刻を決めていく
    vector<ll> ans(N, -1); // ans[i] := 頂点iが頂点Nへ行く際に可能な、最も遅い出発時刻
    ans[N-1] = INF;
    priority_queue<pair<ll,ll>> pq; pq.push({ans[N-1], N-1}); // (この頂点の最も遅い出発時刻, 頂点番号)
    while(!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();

        for(ll v: invG[u]) {
            auto edge = edges[{v,u}];
            ll target_time = ans[u]-edge.c; // この時刻を超えない最も近い時刻に、頂点vから頂点uへ出発したい

            if (target_time < edge.l) {
                // vからuへ出発できない
                ;
            }
            else {
                // target_timeを超えない最も近い時刻を二分探索で探す
                ll l=0, r=edge.k-1;
                while(r-l > 1) {
                    ll mid = (l+r)/2;
                    if (f(mid, target_time, edge)) l = mid;
                    else r = mid;
                }
                ll res_k; // 結局何番目の電車に乗るのか
                if (f(r, target_time, edge)) res_k = r;
                else res_k = l;
                ll res = edge.l + res_k*edge.d;

                // 更新処理
                if (ans[v] < res) {
                    ans[v] = res;
                    pq.push({res, v});
                }
            }
        }
    }

    // 答え
    for(ll i=0; i<N-1; i++) {
        if (ans[i] == -1) cout << "Unreachable" << endl;
        else cout << ans[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}