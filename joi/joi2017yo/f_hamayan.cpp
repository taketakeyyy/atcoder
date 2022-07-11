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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }

ll N, M, X;
ll T[10101];
vector<pair<ll, ll>> E[10101];
ll dist[10101][3][201];
bool vis[10101][3][201];

void solve() {
    cin >> N >> M >> X;
    for(ll i=0; i<N; i++) cin >> T[i];
    for(ll i=0; i<M; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        E[a].push_back({ b, c });
        E[b].push_back({ a, c });
    }

    for(ll i=0; i<N; i++) {
        for(ll lst=0; lst<3; lst++) {
            for(ll x=0; x<X+1; x++) { dist[i][lst][x] = INF; }
        }
    }
    priority_queue<pair<ll, pair<ll,ll>>, vector<pair<ll, pair<ll,ll>>>, greater<pair<ll, pair<ll,ll>>>> que;

    que.push({ 0, {0, 0} });  // {コスト, {部屋番号と最後に入った部屋の温度？, 最後に入った部屋からの累積移動距離}}
    dist[0][0][0] = 0;

    while (!que.empty()) {
        auto q = que.top(); que.pop();

        ll cst = q.first;
        ll cu = q.second.first / 10;
        ll lst = q.second.first % 10;
        ll x = q.second.second;

        if (vis[cu][lst][x]) continue;
        vis[cu][lst][x] = true;

        for (auto p: E[cu]) {
            ll to = p.first;
            ll len = p.second;

            if (T[to] == 0) {
                if (lst == 2 and x + len < X) continue;
                if (dist[to][0][0] >= dist[cu][lst][x] + len) {
                    dist[to][0][0] = dist[cu][lst][x] + len;
                    que.push({ dist[to][0][0], {to * 10 + 0, 0} });
                }
            }
            else if (T[to] == 1) {
                ll x2 = min(X, x + len);
                if (dist[to][lst][x2] >= dist[cu][lst][x] + len) {
                    dist[to][lst][x2] = dist[cu][lst][x] + len;
                    que.push({ dist[to][lst][x2], {to * 10 + lst, x2} });
                }
            }
            else {
                if (lst == 0 and x + len < X) continue;
                if (dist[to][2][0] >= dist[cu][lst][x] + len) {
                    dist[to][2][0] = dist[cu][lst][x] + len;
                    que.push({ dist[to][2][0], {to * 10 + 2, 0} });
                }
            }
        }
    }

    ll ans = INF;
    for(ll lst=0; lst<3; lst++) {
        for(ll x=0; x<X + 1; x++) {
            ans = min(ans, dist[N - 1][lst][x]);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}