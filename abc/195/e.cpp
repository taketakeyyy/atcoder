#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    // ゲームの最適行動⇒後ろから考える
    // dp[i][j] := i文字目まで決まっていて、mod7がjのときの勝敗
    // dp[i+1] は一個前のoldを使って更新していけばいいので、実質dp[j]で済む
    // プレイヤーはS[i]を選ぶか、0を選ぶかのどちらか
    // MODの世界で考えるので、d桁目を見るときに10^d倍を足すが、mod7してOK
    ll N; cin >> N;
    string S; cin >> S;
    string X; cin >> X;
    vector<ll> dp(7);  // dp[j] := mod7がjのときの勝敗
    dp[0] = 1;  // 1:高橋の勝ち 0:青木の勝ち
    ll ten = 1;
    for (int i=N-1; i>=0; i--) {  // 後ろから考える（N-1文字目まで決まっている状態から考える）
        vector<ll> old(7);  // 1つ前の状態のdpテーブル
        swap(dp, old);  // 新しいdpをこれから計算したいので、現在のdpの状態をoldに記録し、dpを初期化する
        for(int j=0; j<7; j++) {
            // dp[j]を求める
            ll nj = (j+ten*(S[i]-'0'))%7;  // S[i]を選んだときのmod7の値
            if (X[i]=='T') {
                // 高橋のターンならば
                // dp[i][j] = dp[i+1][j] | dp[i+1][nj]   と同等のことをしている
                dp[j] = old[j] | old[nj];  // dp[j] = (0を選んだ場合の勝敗) | (S[i]を選んだ場合の勝敗) （どちらかで高橋が勝てるなら、今回も勝てる）
            }
            else {
                // 青木のターンならば
                dp[j] = old[j] & old[nj];  // dp[j] = (0を選んだ場合の勝敗) & (S[i]を選んだ場合の勝敗)　（どちらかで青木が勝てるなら、今回も勝てる）
            }
        }

        ten = (ten*10)%7;
    }

    if (dp[0]==1) {
        cout << "Takahashi" << endl;
    }
    else {
        cout << "Aoki" << endl;
    }
}


int main() {
    solve();
    return 0;
}