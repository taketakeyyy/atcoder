#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve1() {
    ll H, W; cin >> H >> W;
    ll rs, cs; cin >> rs >> cs; rs--; cs--;
    ll rt, ct; cin >> rt >> ct; rt--; ct--;
    vector<string> maze(H);
    for(ll i=0; i<H; i++) {
        string s; cin >> s;
        maze[i] = s;
    }

    // 拡張BFSで解く
    // グラフのコスト情報を方向ごとに拡張する
    // dist[h][w][i] := 位置maze[h][w]において、i方向から来たときのコスト
    vector<vector<vector<ll>>> dist(H, vector<vector<ll>>(W, vector<ll>(4, INF)));

    struct state {
        ll h, w, dir;
    };
    deque<state> deq;
    for (ll i=0; i<4; i++) {
        dist[rs][cs][i] = 0;
        deq.push_back({rs, cs, i});
    }

    const ll dh[4] = {1, 0, -1, 0};  // 下、右、上、左 (移動)
    const ll dw[4] = {0, 1, 0, -1};  // 下、右、上、左 (移動)

    while(!deq.empty()) {
        state u = deq.front(); deq.pop_front();  // キューは前方から取り出すことにする

        for(ll i=0; i<4; i++) {  // 各方向について処理する
            ll nh = u.h + dh[i];
            ll nw = u.w + dw[i];
            ll ncost = dist[u.h][u.w][u.dir] + (u.dir!=i ? 1 : 0); // 方向が変わるならコスト+1

            if (0 <= nh && nh < H && 0 <= nw && nw < W && maze[nh][nw]=='.' && dist[nh][nw][i] > ncost) {
                // コストを更新する
                dist[nh][nw][i] = ncost;
                if (u.dir != i) {
                    deq.push_back({nh, nw, i});  // 方向が変わるなら、コストが高いはずなので後方に追加（後回し）
                }
                else {
                    deq.push_front({nh, nw, i}); // 方向が同じなら、コストは変わらないので前方に追加（優先的に処理したい）
                }
            }
        }
    }

    // 答え
    ll ans = INF;
    for (ll i=0; i<4; i++) {
        ans = min(ans, dist[rt][ct][i]);
    }
    cout << ans << endl;
}


struct State {
    ll h, w, cost, dir;
};
bool operator< (const State &state1, const State &state2) {
    return -state1.cost < -state2.cost;
}
void solve2() {
    // (★) 以下のような迷路に注意。Sから右に行く経路が正解で、答えは1になってほしい。
    // ##G
    // ...
    // .#.
    // S..
    ll H, W; cin >> H >> W;
    ll sh, sw; cin >> sh >> sw; sh--; sw--;
    ll gh, gw; cin >> gh >> gw; gh--; gw--;
    vector<string> maze(H);
    for(ll i=0; i<H; i++) {
        string s; cin >> s;
        maze[i] = s;
    }

    // 優先度突きキューでダイクストラっぽく解きたい
    vector<vector<ll>> dist(H, vector<ll>(W, INF));
    dist[sh][sw] = 0;
    priority_queue<State> que;
    que.push(State{sh, sw, 0, -1});

    ll dh[4] = {-1, 0, 1, 0};
    ll dw[4] = {0, -1, 0, 1};
    while(!que.empty()) {
        auto [h, w, cost, dir] = que.top();
        que.pop();

        for(ll i=0; i<4; i++) {
            ll nh = h + dh[i];
            ll nw = w + dw[i];
            ll ncost = cost + ((dir==-1 || dir==i) ? 0 : 1);

            if (nh < 0 || nh >= H || nw < 0 || nw >= W || maze[nh][nw]=='#') continue;
            if (dist[nh][nw] >= ncost) {  // なぜ>=なのか？それは(★)の状況に対応できるため
                dist[nh][nw] = ncost;
                que.push(State{nh, nw, ncost, i});
            }
        }
    }

    // 答え
    cout << dist[gh][gw] << endl;
    return;
}

struct State3 {
    ll cost, h, w, dir;
};
bool operator< (const State3 &state1, const State3 &state2) {
    return state1.cost < state2.cost;
}
bool operator> (const State3 &state1, const State3 &state2) {  // 昇順にするために必要
    return state1.cost > state2.cost;
}

void solve3() {
    // 拡張ダイクストラで解く
    ll H, W; cin >> H >> W;
    ll sh, sw; cin >> sh >> sw; sh--; sw--;
    ll gh, gw; cin >> gh >> gw; gh--; gw--;
    vector<string> maze(H);
    for(ll i=0; i<H; i++) {
        string s; cin >> s;
        maze[i] = s;
    }

    // 拡張ダイクストラ
    // dist[h][w][dir] := 座標(h,w)での最短距離。dirはどの方向から来たのか(dir=0:上 1:左 2:下 3:右)
    vector dist(H, vector<vector<ll>>(W, vector<ll>(4, INF)));
    for(ll dir=0; dir<4; dir++) { dist[sh][sw][dir] = 0; }
    priority_queue<State3, vector<State3>, greater<State3>> pq;  // 小さい順を維持する優先度付きキュー
    for(ll dir=0; dir<4; dir++) {
        pq.push(State3{0, sh, sw, dir});
    }

    ll dh[4] = {-1, 0, 1, 0};
    ll dw[4] = {0, -1, 0, 1};

    while(!pq.empty()) {
        State3 state = pq.top(); pq.pop();

        if (dist[state.h][state.w][state.dir] < state.cost) { continue; }

        for(ll dir=0; dir<4; dir++) {
            ll nh = state.h + dh[dir];
            ll nw = state.w + dw[dir];
            if (nh<0 || nh>=H || nw<0 || nw>=W || maze[nh][nw]=='#') { continue; }
            ll ncost = state.cost + ((state.dir==dir)? 0 : 1);
            if (dist[nh][nw][dir] > ncost) {
                dist[nh][nw][dir] = ncost;
                pq.push({ncost, nh, nw, dir});
            }
        }
    }

    // 出力
    ll ans = INF;
    for(ll dir=0; dir<4; dir++) { ans = min(ans, dist[gh][gw][dir]); }
    cout << ans << endl;
}


int main() {
    // solve1();
    // solve2();
    solve3();
    return 0;
}