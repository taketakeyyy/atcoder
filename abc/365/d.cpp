#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    string S; cin >> S;

    // dp[i][s] := i番目まで見て、高橋の手がsのときの、最大勝利回数
    vector<ll> dp(3, -1);
    // 初期状態を決める
    if (S[0] == 'R') {
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = -1; // 負けるのでありえない
    }
    else if (S[0] == 'P') {
        dp[0] = -1;
        dp[1] = 0;
        dp[2] = 1;
    }
    else {
        dp[0] = 1;
        dp[1] = -1;
        dp[2] = 0;
    }

    for(ll i=1; i<N; i++) {
        auto olddp = dp;
        for(ll i=0; i<3; i++) dp[i] = 0;

        ll aoki; // 青木の手
        if (S[i] == 'R') aoki = 0;
        else if (S[i] == 'P') aoki = 1;
        else aoki = 2;
        ll winHand = (aoki+1)%3; // 今回高橋が勝つ手
        ll loseHand = (aoki+2)%3; // 今回高橋が負ける手

        for(ll preHand=0; preHand<3; preHand++) { // 前回高橋が出した手
            if (olddp[preHand] == -1) continue;
            for(ll hand=0; hand<3; hand++) { // 今回高橋が出す手
                if (preHand == hand) continue; // 前回と同じ手は出せない
                if (hand == loseHand) continue; // 負ける手はありえない
                if (hand == winHand) {
                    dp[hand] = max(dp[hand], olddp[preHand]+1);
                }
                else {
                    // あいこ
                    dp[hand] = max(dp[hand], olddp[preHand]);
                }
            }
        }
    }

    ll ans = -INF;
    for(ll i=0; i<3; i++) chmax(ans, dp[i]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}