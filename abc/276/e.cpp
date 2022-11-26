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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

ll H, W;
vector<string> grid;
vector<pair<ll,ll>> neighbors;  // Sの隣接マス


bool is_inside(ll i, ll j) {
    return (i>=0 && i<H && j>=0 && j<W);
}

// Sの隣接マスから相異なるマスを2つ選んで、それらを新たな始点、終点とする
// 始点から終点にたどり着けたらOK（必ず経路長4以上になる）
// BFSで解ける(DFSでもいけるらしいが、TLEした)
// 相異なる隣接マス同士が連結しているかの判定をすればいいので、UnionFindでもいける
void solve() {
    cin >> H >> W;
    grid.resize(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }

    // Sを見つける
    ll sh, sw;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (grid[h][w] == 'S') {
                sh = h; sw = w;
            }
        }
    }

    // Sの隣接マス
    for(ll vi=0; vi<4; vi++) {
        ll vh = sh+vy[vi];
        ll vw = sw+vx[vi];
        if (is_inside(vh,vw) && grid[vh][vw]=='.') {
            neighbors.push_back({vh,vw});
        }
    }

    // 相異なる隣接マスを始点、終点にしてBFS探索
    for(ll si=0; si<(ll)neighbors.size(); si++) {
        for(ll ti=si+1; ti<(ll)neighbors.size(); ti++) {
            auto[start_h, start_w] = neighbors[si];
            auto[th, tw] = neighbors[ti];

            // BFS
            deque<pair<ll,ll>> deq; deq.push_back({start_h, start_w});
            vector<vector<bool>> visited(H, vector<bool>(W, false));
            visited[start_h][start_w] = true;
            while(!deq.empty()) {
                auto[h, w] = deq.front(); deq.pop_front();

                if (h==th && w==tw) {
                    cout << "Yes" << endl; return;
                }

                for(ll vi=0; vi<4; vi++) {
                    ll vh = h + vy[vi];
                    ll vw = w + vx[vi];
                    if (!is_inside(vh, vw)) continue;
                    if (grid[vh][vw]!='.') continue;
                    if (visited[vh][vw]) continue;
                    visited[vh][vw] = true;
                    deq.push_back({vh,vw});
                }
            }
        }
    }

    // 出力
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}