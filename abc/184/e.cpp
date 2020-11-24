#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    int H, W;
    cin >> H >> W;

    map<char, vector<pair<int, int>>> warp;  // warp['a']=[(1,2),(2,3)]  // 'a'は1行2列と、2行3列にある
    map<char, bool> warpable;                // ワープ可能か？一度ワープしたことある文字は2度目はしないで良い
    vector<vector<char>> masu(H, vector<char>(W));
    for (int i=0; i<H; i++) {
        string s;
        cin >> s;
        for (int j=0; j<W; j++) {
            masu[i][j] = s[j];
            if (s[j]!='G' && s[j]!='.' && s[j]!='#') {
                warp[s[j]].push_back(make_pair(i,j));
                warpable[s[j]] = true;
            }
        }
    }

    // 幅優先探索で解く（追加はpush_back,取り出しはpop_frontとすることで幅優先探索になるはず）
    vector<vector<int>> dist(H, vector<int>(W, INT_MAX));  // 暫定最短距離
    vector<vector<int>> visited(H, vector<int>(W, false));  // 訪れたか？
    deque<pair<int, int>> q;  // 次に移動するマス目
    q.push_back(warp['S'][0]);
    dist[warp['S'][0].first][warp['S'][0].second] = 0;

    while (!q.empty()) {
        int h, w;
        tie(h, w) = q.front(); q.pop_front();
        visited[h][w] = true;

        if (masu[h][w]=='G') {
            cout << dist[h][w] << endl;
            return;
        }

        int nh, nw;
        if (masu[h][w]!='.' && warpable[masu[h][w]]) {
            // ワープマスの場合
            warpable[masu[h][w]] = false;
            for (auto nh_nw : warp[masu[h][w]]) {  //ここが時間かかる
                tie(nh, nw) = nh_nw;
                if (visited[nh][nw] || !(dist[nh][nw]>dist[h][w]+1)) continue;
                dist[nh][nw] = dist[h][w]+1;
                q.push_back(make_pair(nh, nw));
            }
        }

        // 上下左右移動する
        nh = h-1; nw = w;
        if (nh>=0 && !visited[nh][nw] && masu[nh][nw]!='#' && dist[nh][nw]>dist[h][w]+1) { dist[nh][nw]=dist[h][w]+1; q.push_back(make_pair(nh, nw)); }
        nh = h+1; nw = w;
        if (nh<=H-1 && !visited[nh][nw] && masu[nh][nw]!='#' && dist[nh][nw]>dist[h][w]+1) { dist[nh][nw]=dist[h][w]+1; q.push_back(make_pair(nh, nw)); }
        nh = h; nw = w-1;
        if (nw>= 0 && !visited[nh][nw] && masu[nh][nw]!='#' && dist[nh][nw]>dist[h][w]+1) { dist[nh][nw]=dist[h][w]+1; q.push_back(make_pair(nh, nw)); }
        nh = h; nw = w+1;
        if (nw<=W-1 && !visited[nh][nw] && masu[nh][nw]!='#' && dist[nh][nw]>dist[h][w]+1) { dist[nh][nw]=dist[h][w]+1; q.push_back(make_pair(nh, nw)); }
    }
    cout << -1 << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}