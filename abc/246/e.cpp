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

// ビショップはポーンを飛び越えて移動できない
// BFSで解く。O(頂点数 + 辺数)
// 頂点数 = N^2
// 辺数 = 各頂点につき、高々2Nくらい？
// TLEした。おそらく、探索済みの頂点を何度もループで見ていることが問題(※1)。
// これをなくすには、01-BFSで解く。solve2へ。
void solve() {
    ll N; cin >> N;
    ll ax, ay; cin >> ax >> ay;
    ax--; ay--;
    ll bx, by; cin >> bx >> by;
    bx--; by--;
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];
    // 問題文が(ax,ay), (bx,by)なので、直感的な座標に直す
    swap(ax, ay); swap(bx,by);

    // 座標は盤上に収まっているか？
    auto is_inside = [&N](ll y, ll x) {
        return (x>=0 && x<N && y>=0 && y<N);
    };

    // BFS
    deque<tuple<ll,ll,ll>> deq; deq.push_back({ay,ax,0});
    vector visited(N, vector<ll>(N, false));
    visited[ay][ax] = true;
    while(!deq.empty()) {
        auto[y,x,cost] = deq.front(); deq.pop_front();

        if (y==by && x==bx) {
            cout << cost << endl;
            return;
        }

        for(ll d=1; d<=N; d++) {// 右下移動
            ll ny = y+d; ll nx = x+d;
            if (!is_inside(ny,nx) || S[ny][nx]=='#') break;
            if (visited[ny][nx]) continue;  // (※1)ここを何度も実行してしまうことが問題？
            deq.push_back({ny,nx,cost+1});
            visited[ny][nx] = true;
        }
        for(ll d=1; d<=N; d++) {// 右上移動
            ll ny = y-d; ll nx = x+d;
            if (!is_inside(ny,nx) || S[ny][nx]=='#') break;
            if (visited[ny][nx]) continue;
            deq.push_back({ny,nx,cost+1});
            visited[ny][nx] = true;
        }
        for(ll d=1; d<=N; d++) {// 左上移動
            ll ny = y-d; ll nx = x-d;
            if (!is_inside(ny,nx) || S[ny][nx]=='#') break;
            if (visited[ny][nx]) continue;
            deq.push_back({ny,nx,cost+1});
            visited[ny][nx] = true;
        }
        for(ll d=1; d<=N; d++) {// 左下移動
            ll ny = y+d; ll nx = x-d;
            if (!is_inside(ny,nx) || S[ny][nx]=='#') break;
            if (visited[ny][nx]) continue;
            deq.push_back({ny,nx,cost+1});
            visited[ny][nx] = true;
        }
    }
    cout << -1 << endl;
}

// 01-BFSで解く。O(頂点数 + 辺数)
// 頂点数 = N^2
// 辺数 = 4
// これにより、通常のBFSより格段に早い。
void solve2() {
    ll N; cin >> N;
    ll ax, ay; cin >> ax >> ay;
    ax--; ay--;
    ll bx, by; cin >> bx >> by;
    bx--; by--;
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];
    // 問題文が(ax,ay), (bx,by)なので、直感的な座標に直す
    swap(ax, ay); swap(bx,by);

    // 座標は盤上に収まっているか？
    auto is_inside = [&N](ll y, ll x) -> bool {
        return (x>=0 && x<N && y>=0 && y<N);
    };

    // 01-BFS
    // dist[y][x][dir] := 座標(y,x)で、前回の移動方向がdirのときの最短距離
    vector dist(N, vector<vector<ll>>(N, vector<ll>(4, INF)));
    for(ll dir=0; dir<4; dir++) dist[ay][ax][dir] = 0;
    vector<ll> vy = { -1, -1, 1,  1 };
    vector<ll> vx = { -1,  1, 1, -1 };
    deque<tuple<ll,ll,ll>> deq;  // (y,x,前回の移動方向)
    // 便宜上、スタート地点から1個移動させたやつからスタートしたほうが良い
    for(ll dir=0; dir<4; dir++) {
        ll ny = ay + vy[dir];
        ll nx = ax + vx[dir];
        if (!is_inside(ny,nx) || S[ny][nx]=='#') continue;
        dist[ny][nx][dir] = 1;
        deq.push_back({ny,nx,dir});
    }
    while(!deq.empty()) {
        auto[y,x,pre_dir] = deq.front(); deq.pop_front();
        ll cost = dist[y][x][pre_dir];

        // 01-BFSはコスト小さい順にキューに入っている。
        if (y==by && x==bx) {
            cout << cost << endl;
            return;
        }

        // ビショップ移動
        for(ll dir=0; dir<4; dir++) {
            ll ny = y + vy[dir];
            ll nx = x + vx[dir];
            if (!is_inside(ny,nx) || S[ny][nx]=='#') continue;
            if (dir == pre_dir) {
                // 前回と移動方向が同じなら、コスト0で移動
                if (dist[ny][nx][dir] > cost) {
                    dist[ny][nx][dir] = cost;
                    deq.push_front({ny,nx,dir});  // コスト0移動はfrontに入れる
                }
            }
            else {
                // 前回と移動方向が異なるなら、コスト+1で移動
                if (dist[ny][nx][dir] > cost+1) {
                    dist[ny][nx][dir] = cost+1;
                    deq.push_back({ny,nx,dir});  // コスト+1移動はbackに入れる
                }
            }
        }
    }
    cout << -1 << endl;
}

// 01-BFSで解く。O(頂点数 + 辺数)
// これにより、通常のBFSより格段に早い。
void solve3() {
    ll N; cin >> N;
    ll ax, ay; cin >> ax >> ay;
    ax--; ay--;
    ll bx, by; cin >> bx >> by;
    bx--; by--;
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];
    // 問題文が(ax,ay), (bx,by)なので、直感的な座標に直す
    swap(ax, ay); swap(bx,by);

    // 座標は盤上に収まっているか？
    auto is_inside = [&N](ll y, ll x) -> bool {
        return (x>=0 && x<N && y>=0 && y<N);
    };

    // 01-BFS
    // dist[y][x][dir] := 座標(y,x)で、前回の移動方向がdirのときの最短距離
    vector dist(N, vector<vector<ll>>(N, vector<ll>(4, INF)));
    for(ll dir=0; dir<4; dir++) dist[ay][ax][dir] = 0;
    vector<ll> vy = { -1, -1, 1,  1 };
    vector<ll> vx = { -1,  1, 1, -1 };
    deque<tuple<ll,ll,ll>> deq;  // (y,x,前回の移動方向)
    // 便宜上、スタート地点から1個移動させたやつからスタートしたほうが良い
    for(ll dir=0; dir<4; dir++) {
        ll ny = ay + vy[dir];
        ll nx = ax + vx[dir];
        if (!is_inside(ny,nx) || S[ny][nx]=='#') continue;
        dist[ny][nx][dir] = 1;
        deq.push_back({ny,nx,dir});
    }
    while(!deq.empty()) {
        auto[y,x,pre_dir] = deq.front(); deq.pop_front();
        ll cost = dist[y][x][pre_dir];

        // ビショップ移動
        for(ll dir=0; dir<4; dir++) {
            ll ny = y + vy[dir];
            ll nx = x + vx[dir];
            if (!is_inside(ny,nx) || S[ny][nx]=='#') continue;
            if (dir == pre_dir) {
                // 前回と移動方向が同じなら、コスト0で移動
                if (dist[ny][nx][dir] > cost) {
                    dist[ny][nx][dir] = cost;
                    deq.push_front({ny,nx,dir});  // コスト0はfrontに入れる
                }
            }
            else {
                // 前回と移動方向が異なるなら、コスト+1で移動
                if (dist[ny][nx][dir] > cost+1) {
                    dist[ny][nx][dir] = cost+1;
                    deq.push_back({ny,nx,dir});  // コスト+1はbackに入れる
                }
            }
        }
    }

    ll ans = INF;
    for(ll dir=0; dir<4; dir++) {
        ans = min(ans, dist[by][bx][dir]);
    }
    cout << ((ans==INF) ? -1 : ans) << endl;
}

int main() {
    // solve();
    solve2();
    // solve3();
    return 0;
}