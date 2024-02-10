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
    ll N; cin >> N;
    vector<string> grid(N);
    for(ll i=0; i<N; i++) {
        cin >> grid[i];
    }

    auto where_players = [&](vector<string> &grid) -> pair<pair<ll,ll>,pair<ll,ll>> {
        pair<ll,ll> p1 = {-1,-1};
        pair<ll,ll> p2 = {-1,-1};
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if (grid[i][j]=='P') {
                    if (p1.first == -1) {
                        // p1を設定
                        p1.first = i;
                        p1.second = j;
                    }
                    else {
                        // p2を設定
                        p2.first = i;
                        p2.second = j;
                    }
                }
            }
        }
        return {p1, p2};
    };

    auto move = [&](pair<ll,ll> p, ll dir) -> pair<ll,ll>{
        ll nh = p.first + vy[dir];
        ll nw = p.second + vx[dir];
        if (nh==N) nh = N-1;
        if (nh<0) nh=0;
        if (nw==N) nw = N-1;
        if (nw<0) nw=0;

        if (grid[nh][nw]=='#') return p;
        return {nh,nw};
    };

    // unordered_setに入れるために数字化
    auto to_num = [&](pair<ll,ll>&p1, pair<ll,ll>&p2) -> ll {
        ll n1 = p1.first*N + p1.second;
        ll n2 = p2.first*N + p2.second;
        return n1*4000 + n2;
    };

    auto bfs = [&]() {
        auto[p1, p2] = where_players(grid);
        deque<tuple<pair<ll,ll>,pair<ll,ll>,ll>> deq; // (p1,p2,コスト)
        deq.push_back({p1,p2,0});
        unordered_set<ll> visited;
        visited.insert(to_num(p1,p2));
        while(!deq.empty()) {
            auto[p1,p2,cost] = deq.front(); deq.pop_front();

            if (p1 == p2) {
                return cost;
            }

            // 次の探索
            for(ll dir=0; dir<4; dir++) {
                auto np1 = move(p1, dir);
                auto np2 = move(p2, dir);
                if (np1==p1 and np2==p2) continue;
                if (visited.count(to_num(np1,np2))) continue;
                visited.insert(to_num(np1,np2));
                deq.push_back({np1,np2,cost+1});
            }
        }
        return -1LL;
    };
    ll ans = bfs();
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}