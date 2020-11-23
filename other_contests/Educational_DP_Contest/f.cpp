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
    /* 解説AC
    https://kyopro-friends.hatenablog.com/entry/2019/01/12/231000

    dp[i][j] := sをi文字、tをj文字目まで見たときの最長共通部分列の長さ

    */
    string S, T;
    cin >> S; cin >> T;
    vector<vector<int>> dp(S.size()+1, vector<int>(T.size()+1, 0));

    for (int i=1; i<S.size()+1; i++) {
        for (int j=1; j<T.size()+1; j++) {
            if (S[i-1]==T[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    // dp[S.size()][T.size()] が求める長さ

    // 実際の文字列を構成していく
    // 具体的に文字列を作るのはDP配列を逆にたどればできる
    // * もしS[i]==T[j]なら、求める最長共通部分列の最後の文字はS[i]
    //     - それより前の部分はdp[i-1][j-1]の結果からわかる
    // * もしS[i]!=T[j]なら、どっちかの最後の文字は使わないから、dpの値が減らない方に移動すればよい
    int len = dp[S.size()][T.size()];
    vector<char> ans(len);  // 求める文字列
    int i = S.size();
    int j = T.size();
    while (len>0) {
        if (S[i-1]==T[j-1]) {
            // 求める最長共通部分列の最後の文字はS[i]
            ans[len-1] = S[i-1];
            i--; j--; len--;
            continue;
        }
        else if (dp[i][j]==dp[i-1][j]) {
            // dpの値が減らない方へ移動する
            i--;
            continue;
        }
        else {
            // dpの値が減らない方へ移動する
            j--;
            continue;
        }
    }

    for (int a=0; a<ans.size(); a++) {
        cout << ans[a];
    }
    cout << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}