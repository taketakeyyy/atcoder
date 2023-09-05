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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll A, B; cin >> A >> B;

    // [0,N]の禁止されてる数の個数を返す
    auto f = [&](ll N) -> ll{
        string S = to_string(N);

        // dp[i][j] := i桁目まで見て、未満フラグがjのときの、禁止されてない数の個数
        vector<ll> dp(2, 0);
        for(ll i=0; i<(ll)S.size(); i++) {
            auto olddp = dp;
            for(ll j=0; j<2; j++) dp[j]=0; // 初期化

            ll n = S[i]-'0'; // i桁目の数

            if (i == 0) {
                // 初期値を埋める
                if (n==9) {
                    dp[0] = 0;
                    dp[1] = 8; // 9と4を除く[0,n]のn-1通り
                }
                else if (n>4) {
                    dp[0] = 1;
                    dp[1] = n+1-2; // nと4を除く[0,n]のn通り
                }
                else if (n==4) {
                    dp[0] = 0;
                    dp[1] = n+1-1; // 4を除く[0,n]のn通り
                }
                else {
                    dp[0] = 1;
                    dp[1] = n+1-1; // nを除く[0,n]のn通り
                }
            }
            else {
                // dpを埋める
                if (n==9) {
                    dp[0] = 0;
                    dp[1] = olddp[0]*8 + olddp[1]*8;
                }
                else if (n>4) {
                    dp[0] = olddp[0];
                    dp[1] = olddp[0]*(n+1-2) + olddp[1]*8;
                }
                else if (n==4) {
                    dp[0] = 0;
                    dp[1] = olddp[0]*(n+1-1) + olddp[1]*8;
                }
                else {
                    dp[0] = olddp[0];
                    dp[1] = olddp[0]*(n+1-1) + olddp[1]*8;
                }
            }
        }

        // [0,N]の範囲の禁止されてる数の個数を求める
        ll ret = N+1 - dp[0] - dp[1];
        return ret;
    };

    ll ans = f(B) - f(A-1);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}