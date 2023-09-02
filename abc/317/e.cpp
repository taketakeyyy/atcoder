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
    ll H, W; cin >> H >> W;
    vector<string> A(H);
    for(ll i=0; i<H; i++) {
        cin >> A[i];
    }

    // 視線を埋める
    auto apply_sisen_horizon = [&](char dir, ll start, ll terminal, ll step) -> void {
        for(ll h=0; h<H; h++) {
            bool is_looking = false;
            for(ll w=start, w!=terminal; w+=step) {
                if (A[h][w] == dir) {
                    is_looking = true;
                    continue;
                }
                if (is_looking) {
                    if (A[h][w]=='.' || A[h][w]=='!') {
                        A[h][w] = '!';
                        continue;
                    }
                    else {
                        // 障害物や人に当たった
                        is_looking = false;
                        continue;
                    }
                }
            }
        }
    };
    auto apply_sisen_vertical = [&](char dir, ll start, ll terminal, ll step) -> void {
        for(ll w=0; w<W; w++) {
            bool is_looking = false;
            for(ll h=start, h!=terminal; h+=step) {
                if (A[h][w] == dir) {
                    is_looking = true;
                    continue;
                }
                if (is_looking) {
                    if (A[h][w]=='.' || A[h][w]=='!') {
                        A[h][w] = '!';
                        continue;
                    }
                    else {
                        // 障害物や人に当たった
                        is_looking = false;
                        continue;
                    }
                }
            }
        }
    };
    apply_sisen_horizon('>', 0, W, 1); // 左から右へ走査
    apply_sisen_horizon('<', W-1, -1, -1); // 右から左へ走査
    apply_sisen_vertical('v', 0, H, 1); // 上から下へ走査
    apply_sisen_vertical('^', H-1, -1, -1); // 下から上へ走査

    // スタートを探す
    ll sh=-1, sw=-1;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (A[h][w] == 'S') {
                sh = h;
                sw = w;
            }
        }
    }

    // 内側に入っているか？
    auto is_inside = [&](ll h, ll w) -> bool {
        return (h>=0 && h<H && w>=0 && w<W);
    };

    // BFS
    deque<tuple<ll,ll,ll>> deq; // (h,w,cost)
    deq.push_back({sh, sw, 0});
    vector visited(H, vector<bool>(W, false));
    visited[sh][sw] = true;
    while(!deq.empty()) {
        auto[h, w, c] = deq.front();
        deq.pop_front();

        // 終了条件
        if (A[h][w] == 'G') {
            cout << c << endl;
            return;
        }

        // 探索
        for(ll vi=0; vi<4; vi++) {
            ll nh = h + vy[vi];
            ll nw = w + vx[vi];
            if (!is_inside(nh,nw)) continue;
            if (A[nh][nw]=='.' || A[nh][nw]=='G') {
                if (visited[nh][nw]) continue;
                visited[nh][nw] = true;
                deq.push_back({nh,nw,c+1});
            }
        }
    }
    cout << -1 << endl;
    return;
}


int main() {
    solve();
    return 0;
}