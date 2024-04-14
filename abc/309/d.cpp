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
    ll N1, N2, M; cin >> N1 >> N2 >> M;
    vector<set<ll>> G1(N1);
    vector<set<ll>> G2(N2);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        if (1LL<=a && a<=N1) {
            a--; b--;
            G1[a].insert(b);
            G1[b].insert(a);
        }
        else {
            a-=N1; b-=N1;
            a--; b--;
            G2[a].insert(b);
            G2[b].insert(a);
        }
    }

    vector<ll> dist1(N1,-1); // 頂点1からN1クラスの各頂点までの距離
    dist1[0] = 0;
    vector<ll> dist2(N2,-1); // 頂点N1+N2からN2クラスの各頂点までの距離
    dist2[N2-1] = 0;

    // dist1を求める
    {
        deque<pair<ll,ll>> deq;
        deq.push_back({0,0});
        vector<bool> visited(N1, false);
        visited[0] = true;
        while(!deq.empty()) {
            auto[u, cost] = deq.front(); deq.pop_front();

            for(ll v: G1[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                dist1[v] = cost+1;
                deq.push_back({v,cost+1});
            }
        }
    }

    // dist2を求める
    {
        deque<pair<ll,ll>> deq;
        deq.push_back({N2-1,0});
        vector<bool> visited(N2, false);
        visited[N2-1] = true;
        while(!deq.empty()) {
            auto[u, cost] = deq.front(); deq.pop_front();

            for(ll v: G2[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                dist2[v] = cost+1;
                deq.push_back({v,cost+1});
            }
        }
    }

    // dist1の最大とdist2の最大の頂点同士を繋げたものが答えのグラフになる
    ll ans = 1;
    {
        ll longest = 0;
        for(ll c: dist1) {
            longest = max(longest, c);
        }
        ans += longest;
    }
    {
        ll longest = 0;
        for(ll c: dist2) {
            longest = max(longest, c);
        }
        ans += longest;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}