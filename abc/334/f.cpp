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
    ll N, K; cin >> N >> K;
    ll sx, sy; cin >> sx >> sy;
    vector<ll> X(N), Y(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i];
    }

    auto dist = [&](pair<ll,ll> a, pair<ll,ll> b) -> double {
        ll x1 = a.first; ll y1 = a.second;
        ll x2 = b.first; ll y2 = b.second;
        double res = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        return res;
    };

    // dp[i][k]
    priority_queue<tuple<double,ll,ll>, vector<tuple<double,ll,ll>>, greater<tuple<double,ll,ll>>> pq;  // 小さい順を維持する優先度付きキュー (コスト, アイテム個数, 現在いる子供の家番号)
    pq.push({dist(make_pair(sx,sy), make_pair(X[0],Y[0])),K-1,0});
    while(!pq.empty()) {
        auto[cost, restK, u] = pq.top(); pq.pop();

        // 終了条件
        if (u == N-1) {
            // 家に帰る
            cost += dist({sx,sy}, {X[u],Y[u]});
            printf("%.10lf\n", cost);
            return;
        }

        if (restK >= 1) {
            {// 家に帰ってから次の家に行く場合
                double res = dist({X[u], Y[u]}, {sx,sy});
                res += dist({sx,sy}, {X[u+1], Y[u+1]});
                pq.push({cost+res, K-1, u+1});
            }
            {// 直接次の家に行く場合
                double res = dist({X[u], Y[u]}, {X[u+1], Y[u+1]});
                pq.push({cost+res, restK-1, u+1});
            }
        }
        else {
            // 家に帰ってから次の家に行くしかできない
                double res = dist({X[u], Y[u]}, {sx,sy});
                res += dist({sx,sy}, {X[u+1], Y[u+1]});
                pq.push({cost+res, K-1, u+1});
        }
    }
}


int main() {
    solve();
    return 0;
}