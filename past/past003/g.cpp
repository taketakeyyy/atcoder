#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    /*
    https://www.hamayanhamayan.com/entry/2020/06/06/230814
    */
    int N, X, Y;
    vector<vector<bool>> block(505, vector<bool>(505, false));  // 障害物がある：true
    const int MX = 500;  // マスの最大値
    const int BASE = 250;
    vector<vector<bool>> visited(505, vector<bool>(505, false));  // 訪れたことがあるならtrue
    vector<vector<int>> dist(505, vector<int>(505, 0));  // 各マスへの最短距離
    vector<int> dx = {1, 0,-1, 1,-1, 0};
    vector<int> dy = {1, 1, 1, 0, 0,-1};

    cin >> N >> X >> Y;
    X += BASE; Y += BASE;
    for(int i=0; i<N; i++) {
        int x, y;
        cin >> x >> y;
        block[x+BASE][y+BASE] = true;
    }

    queue<pair<int, int>> que;
    que.push({BASE, BASE});
    visited[BASE][BASE] = true;

    while (!que.empty()) {
        int x, y;
        tie(x, y) = que.front(); que.pop();

        if (x==X && y==Y) {
            cout << dist[x][y] << endl;
            return;
        }

        for (int d=0; d<6; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (0 <= nx && nx < MX && 0 <= ny && ny < MX) {
                if (block[nx][ny]) continue;
                if (visited[nx][ny]) continue;

                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                que.push({nx, ny});
            }
        }
    }

    if (visited[X][Y]) cout << dist[X][Y] << endl;
    else cout << -1 << endl;
}


void solve2(){
    /*
    https://www.hamayanhamayan.com/entry/2020/06/06/230814
    */
    const int INF = 2*pow(10,9);
    int N, X, Y;
    vector<vector<bool>> block(505, vector<bool>(505, false));  // 障害物がある or 訪れたことがある：true
    const int MX = 500;  // マスの最大値
    const int BASE = 250;
    vector<vector<int>> dist(505, vector<int>(505, INF));  // 各マスへの最短距離
    dist[BASE][BASE] = 0;
    vector<int> dx = {1, 0,-1, 1,-1, 0};
    vector<int> dy = {1, 1, 1, 0, 0,-1};

    cin >> N >> X >> Y;
    X += BASE; Y += BASE;
    for(int i=0; i<N; i++) {
        int x, y;
        cin >> x >> y;
        block[x+BASE][y+BASE] = true;
    }

    queue<pair<int, int>> que;
    que.push({BASE, BASE});
    block[BASE][BASE] = true;

    while (!que.empty()) {
        int x, y;
        tie(x, y) = que.front(); que.pop();

        if (x==X && y==Y) {
            cout << dist[x][y] << endl;
            return;
        }

        for (int d=0; d<6; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (0 <= nx && nx < MX && 0 <= ny && ny < MX) {
                if (block[nx][ny]) continue;

                block[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                que.push({nx, ny});
            }
        }
    }
    /*
    if (block[X][Y]) cout << dist[X][Y] << endl;
    else cout << -1 << endl;
    */
   cout << -1 << endl;
}


int main(int argc, char const *argv[]){
    solve2();
    return 0;
}