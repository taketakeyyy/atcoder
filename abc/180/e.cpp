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


void solve(){
    /* 解説AC
     * dp[S][v] := 現在の都市がvのときで、今まで訪れた都市集合がSのときの、最小コスト
     * v -> u :コストdist[v][u]
     * chmin(dp[S+u][u], dp[S][v]+dist[v][u])
     *
     * 計算量
     * S: 2^N
     * v: N
     * 遷移がN通り
     * なので、O(2^N * N^2)
     * */
    int n;
    cin >> n;
    vector<int> x(n), y(n), z(n);
    rep(i, n) cin >> x[i] >> y[i] >> z[i];
    int n2 = 1<<n;  // 2のn乗
    vector<vector<int>> dp(n2, vector<int>(n, INF));

    /*
     * distを前計算しておく
     * dist[i][j] := iからjへ移動するときのコスト
     * */
    vector<vector<int>> dist(n, vector<int>(n));
    rep(i,n) rep(j,n) {
        int now = abs(x[i]-x[j]);
        now += abs(y[i]-y[j]);
        now += max(0, z[j]-z[i]);
        dist[i][j] = now;
    }

    // dpの最初の遷移の初期化
    for (int i=1; i<n; i++) {
        dp[1<<i][i] = dist[0][i];  // 0からiへ移動したときを初期状態とする
    }

    // dp計算
    for (int i=0; i<n2; i++) {
        for (int j=0; j<n; j++) {
            if (~i>>j&1) continue;  // iのj-bit目が立っていなければcontinue（jはまだ訪問していなければcontinue）
            for (int k=0; k<n; k++) {
                if (i>>k&1) continue;  // kが訪問済みならばcontinue
                // jが訪問済みで、kはまだ訪問していなければdp更新
                chmin(dp[i|1<<k][k], dp[i][j]+dist[j][k]);
            }
        }
    }
    cout << dp[n2-1][0] << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}