#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

vector<vector<int>> grid;
int N, K;
int ans;

void dfs(int now, int cost, set<int> &visited) {
    if (visited.size() == N-1) {
        if (cost + grid[now][0] == K) {
            ans++;
        }
        visited.erase(now);
        return;
    }

    for (int i=1; i<N; i++) {
        if (visited.count(i)) continue;
        visited.insert(i);
        dfs(i, cost+grid[now][i], visited);
    }
    visited.erase(now);
    return;
}


void solve(){
    cin >> N >> K;
    grid.resize(N);
    for (int i=0; i<N; i++) {
        grid[i].resize(N, 0);
        for (int j=0; j<N; j++) {
            cin >> grid[i][j];
        }
    }

    ans = 0;
    set<int> visited;
    for (int i=1; i<N; i++) {
        dfs(i, grid[0][i], visited);
    }

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}