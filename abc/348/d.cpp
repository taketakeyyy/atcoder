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
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }
    ll N; cin >> N;
    map<pair<ll,ll>,ll> med;
    for(ll i=0; i<N; i++) {
        ll r, c, e; cin >> r >> c >> e;
        r--; c--;
        med[{r,c}] = e;
    }

    // スタート地点とゴール地点を探す
    pair<ll,ll> sp, tp;
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            if (grid[i][j] == 'S') sp = {i,j};
            if (grid[i][j] == 'T') tp = {i,j};
        }
    }

    // スタート地点に薬がないなら終わり
    if (med[sp] <= 0) {
        cout << "No" << endl;
        return;
    }

    auto is_inside = [&](ll y, ll x) {
        return y>=0 and y<H and x>=0 and x<W;
    };

    // pq
    priority_queue<tuple<ll,ll,ll>> pq; // (エネルギー,y,x)
    pq.push({med[sp], sp.first, sp.second});
    vector memo(H, vector(W, -1LL));
    memo[sp.first][sp.second] = med[sp];
    while(!pq.empty()) {
        auto[e, y, x] = pq.top(); pq.pop();

        // 終了条件
        if (tp == make_pair(y,x)) {
            cout << "Yes" << endl;
            return;
        }
        if (e == 0) continue;

        for(ll vi=0; vi<4; vi++) {
            ll ny = y + vy[vi];
            ll nx = x + vx[vi];
            ll ne = e-1;
            chmax(ne, med[{ny,nx}]);
            if (!is_inside(ny,nx)) continue;
            if (grid[ny][nx]=='#') continue;
            if (ne <= memo[ny][nx]) continue;
            memo[ny][nx] = ne;
            pq.push({ne,ny,nx});
        }
    }
    cout << "No" << endl;
}


// 解説AC
// 薬を頂点とする有向グラフを作り、SからTへ移動可能ならYes
void solve2() {
    ll H, W; cin >> H >> W;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }
    ll N; cin >> N;
    map<pair<ll,ll>,ll> med;
    for(ll i=0; i<N; i++) {
        ll r, c, e; cin >> r >> c >> e;
        r--; c--;
        med[{r,c}] = e;
    }

    // スタート地点とゴール地点を探す
    pair<ll,ll> sp, tp;
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            if (grid[i][j] == 'S') sp = {i,j};
            if (grid[i][j] == 'T') tp = {i,j};
        }
    }

    // スタート地点に薬がないなら終わり
    if (med[sp] <= 0) {
        cout << "No" << endl;
        return;
    }

    auto is_inside = [&](ll y, ll x) {
        return y>=0 and y<H and x>=0 and x<W;
    };

    vector G(H, vector(W, vector<pair<ll,ll>>())); // G[y][x] := 薬(y,x)から到達可能な薬（とゴール）のリスト
    // 薬spから到達可能な薬（とゴール）を探索する
    auto bfs = [&](pair<ll,ll> sp) {
        deque<tuple<ll,ll,ll>> deq; // (y,x,エネルギー)
        deq.push_back({sp.first, sp.second, med[sp]});
        vector visited(H, vector(W, false));
        visited[sp.first][sp.second] = true;
        while(!deq.empty()) {
            auto[y, x, e] = deq.front(); deq.pop_front();

            // 終了条件
            if (e==0) continue;

            // 次の探索
            for(ll vi=0; vi<4; vi++) {
                ll ny = y + vy[vi];
                ll nx = x + vx[vi];
                ll ne = e - 1;
                if (!is_inside(ny,nx)) continue;
                if (grid[ny][nx]=='#') continue;
                if (visited[ny][nx]) continue;
                visited[ny][nx] = true;
                deq.push_back({ny,nx,ne});
                if (med.count({ny,nx})) {
                    G[sp.first][sp.second].push_back({ny,nx});
                }
                if (grid[ny][nx]=='T') {
                    G[sp.first][sp.second].push_back({ny,nx});
                }
            }
        }
    };
    for(auto[key, val]: med) {
        bfs(key);
    }

    {// SからTへ移動可能か？
        auto bfs2 = [&]() {
            deque<pair<ll,ll>> deq;
            deq.push_back(sp);
            set<pair<ll,ll>> visited;
            visited.insert(sp);
            while(!deq.empty()) {
                auto p = deq.front(); deq.pop_front();

                // 終了条件
                if (p == tp) {
                    return true;
                }

                // 次の探索
                for(pair<ll,ll> np: G[p.first][p.second]) {
                    if (visited.count(np)) continue;
                    visited.insert(np);
                    deq.push_back(np);
                }
            }
            return false;
        };
        bool ans = bfs2();
        if (ans) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

int main() {
    // solve();
    solve2();
    return 0;
}