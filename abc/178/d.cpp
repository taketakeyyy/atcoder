#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    /*解説AC
    https://youtu.be/yLkJZXkB6D0?t=2549

    S個のoを考える
    ooooo...o
    これの間にしきりを入れる。例えばS=7なら、
    |ooo|oooo
    これは、数列[3,4]を表している。
    このように、oと|を使っていくつの数列を作れるか考える。
    なお、数列の値は10以上でも構わない。（S=16のとき、数列[3,13]でもOK）

    dp[i] := 最後に切った位置がiのときの、数列の数
    */
    int S;
    cin >> S;
    ll dp[2001] = {0};
    dp[0] = 1;

    for (int i=1; i<S+1; i++) {
        for (int j=0; j<(i-3)+1; j++) {
            dp[i] += dp[j];
            dp[i] %= MOD;
        }
    }

    cout << dp[S] << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}