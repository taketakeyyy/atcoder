#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;

int calc_cost(int a, int b, int c, int p, int q, int r) {
    // コスト計算
    return abs(p-a) + abs(q-b) + max(0, r-c);
}

void solve(){
    int N;
    cin >> N;
    vector<int> X(N,0);
    vector<int> Y(N,0);
    vector<int> Z(N,0);
    for (int i=0; i<N; i++) {
        cin >> X[i] >> Y[i] >> Z[i];
    }

    // dp[S][i] := 現在位置が都市iで、今まで訪れた都市集合がSのときの最小コスト
    vector<vector<int>> dp(pow(2,N), vector<int>(N, INT_MAX));

    // 都市0からスタートなので、都市0から都市iへのコストは計算しておく（都市0は訪問したこと無い扱い）
    for(int i=1; i<N; i++) {
        dp[1<<i][i] = calc_cost(X[0], Y[0], Z[0], X[i], Y[i], Z[i]);
    }

    // dpを埋めていく
    for (int bit=0; bit<pow(2,N); bit++) {
        for (int i=0; i<N; i++) {  // 現在の都市i
            if (~bit>>i&1) continue; // iはまだ訪れていない
            for (int j=0; j<N; j++) {  // 次に行く都市j
                if (bit>>j&1) continue; // jはすでに訪れている
                // iが訪問済みで、jはまだ訪れていないなら、
                dp[bit|1<<j][j] = min(dp[bit|1<<j][j], dp[bit][i]+calc_cost(X[i], Y[i], Z[i], X[j], Y[j], Z[j]));
            }
        }
    }
    cout << dp[pow(2,N)-1][0] << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}