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
const long long INF = LONG_LONG_MAX/2 - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 2^18 = 262144
void solve() {
    ll H, W, T; cin >> H >> W >> T;
    vector<string> A(H);
    for(ll i=0; i<H; i++) {
        cin >> A[i];
    }

    // スタート地点とゴール地点を覚えておく
    // 各お菓子に番号をつける
    map<pair<ll,ll>,ll> pos2id; // 座標ID
    map<ll,pair<ll,ll>> id2pos; // 各位置
    ll okashi_num; // (お菓子の数)
    ll pos_num; // 全地点の数（お菓子の数+スタート+ゴール）
    ll start_id;
    ll goal_id;
    {
        ll id = 0;
        pair<ll,ll> start_pos;
        pair<ll,ll> goal_pos;
        for(ll h=0; h<H; h++) {
            for(ll w=0; w<W; w++) {
                if (A[h][w] == 'o') {
                    pos2id[{h,w}] = id;
                    id2pos[id] = {h,w};
                    id++;
                }
                if (A[h][w] == 'S') start_pos = {h,w};
                if (A[h][w] == 'G') goal_pos = {h,w};
            }
        }
        okashi_num = id;
        // ゴール位置
        goal_id = id;
        pos2id[goal_pos] = id;
        id2pos[id] = goal_pos;
        id++;
        // スタート位置
        start_id = id;
        pos2id[start_pos] = id;
        id2pos[id] = start_pos;
        id++;
        pos_num = id;
    }

    // 全頂点対の最短経路をBFSで求める
    vector dist(pos_num, vector<ll>(pos_num, INF));
    auto is_inside = [&](ll h, ll w) {
        return (h>=0 && h<H && w>=0 && w<W);
    };
    auto bfs = [&](ll sh, ll sw) {
        deque<tuple<ll,ll,ll>> deq;
        deq.push_back({sh,sw,0});
        vector visited(H, vector<ll>(W, false));
        visited[sh][sw] = true;
        while(!deq.empty()) {
            auto[h,w,cost] = deq.front(); deq.pop_front();

            for(ll vi=0; vi<4; vi++) {
                ll nh = h + vy[vi];
                ll nw = w + vx[vi];
                ll ncost = cost + 1;
                if (!is_inside(nh,nw)) continue;
                if (A[nh][nw] == '#') continue;
                if (visited[nh][nw]) continue;
                visited[nh][nw] = true;
                if (A[nh][nw]=='o' || A[nh][nw]=='S' || A[nh][nw]=='G') {
                    dist[pos2id[{sh,sw}]][pos2id[{nh,nw}]] = ncost;
                }
                deq.push_back({nh,nw,ncost});
            }
        }
    };
    for(ll id=0; id<pos_num; id++) {
        auto[h,w] = id2pos[id];
        bfs(h,w);
    }
    // 終了条件忘れずに！
    if (dist[start_id][goal_id] > T) {
        cout << -1 << endl;
        return;
    }

    // bidDPで巡回セールスマン問題を解く
    // dp[bit][i] := 訪問状態がbitで、現在位置がiのときの最小コスト
    vector dp(1LL<<okashi_num, vector<ll>(okashi_num, INF));
    // スタートから、各位置（各お菓子）の初期コストは計算しておく
    for(ll i=0; i<okashi_num; i++) {
        dp[1LL<<i][i] = dist[start_id][i];
    }
    // bitDPで解く
    for(ll bit=0; bit<(1LL<<(okashi_num)); bit++) {
        for(ll i=0; i<okashi_num; i++) { // 現在の位置i
            if (~bit>>i&1) continue; // iはまだ訪れてない
            for(ll j=0; j<okashi_num; j++) { // 次の位置j
                if (bit>>j&1) continue; // jは既に訪れている
                if (dp[bit][i]==INF || dist[i][j]==INF) continue; // オーバーフロー対策
                dp[bit|1<<j][j] = min(dp[bit|1<<j][j], dp[bit][i]+dist[i][j]);
            }
        }
    }

    // bitDPで解いた最小コスト+ゴールまでのコストがT以下ならOK。
    // そのときの訪問したお菓子の数を求め、最大数を求める
    ll ans = 0;
    for(ll bit=0; bit<(1LL<<okashi_num); bit++) {
        // 訪問したお菓子の数を数える
        ll visited_num = 0;
        for(ll d=0; d<okashi_num; d++) {
            if (bit>>d&1) visited_num++;
        }

        // 現在位置iからゴールまでのコストがT以下ならOK
        for(ll i=0; i<okashi_num; i++) {
            if (~bit>>i&1) continue;
            if (dp[bit][i]==INF || dist[i][goal_id]==INF) continue;
            if (dp[bit][i]+dist[i][goal_id] <= T) {
                ans = max(ans, visited_num);
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}