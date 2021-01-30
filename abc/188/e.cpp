#include <bits/stdc++.h>
using namespace std;


void solve(){
    int N, M;
    cin >> N >> M;
    vector<int> As(N);
    for (int i=0; i<N; i++) {
        cin >> As[i];
    }
    vector<vector<int>> paths(N);
    for (int i=0; i<M; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        paths[x].push_back(y);
    }

    // dp[i] := 町iに到達できる町集合Y(iを含まず)における、金の最安値
    vector<int> dp(N, INT_MAX);
    for (int i=0; i<N; i++) {
        for (int v :paths[i]) {
            dp[v] = min(dp[v], min(dp[i], As[i]));
        }
    }
    // 上はO(NM)じゃない
    // O(NM) = M回の操作をN回
    // 今回のpaths[i]は、最悪ケースでM回の操作が1回あるが、その場合は他のpaths[i]は0回になるので、O(NM)とは言えない

    // 答え
    int ans = INT_MIN;
    for (int i=0; i<N; i++) {
        ans = max(ans, As[i]-dp[i]);
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}