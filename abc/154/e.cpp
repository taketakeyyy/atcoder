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
    string N; cin >> N;
    ll K; cin >> K;
    ll D = N.size(); // Nの桁数

    // dp[i][j][k] := 左からi桁目まで見て、N未満フラグがjで、0でない数字がk個のときの個数
    vector dp(D, vector<vector<ll>>(2, vector<ll>(K+1, 0)));
    // 初期値を埋める
    dp[0][0][0] = 0;
    dp[0][0][1] = 1;
    dp[0][1][0] = 1;
    if (N[0]-'0' > 1) {
        dp[0][1][1] = (N[0]-'0')-1;
    }
    // dpを埋める
    for(ll i=1; i<D; i++) {
        ll n = N[i]-'0'; // i桁目の数字

        // N未満フラグ0への遷移
        for(ll k=0; k<K+1; k++) {
            if (n == 0) {
                dp[i][0][k] = dp[i-1][0][k]; // i桁目にnを選ぶ
            }
            else {
                if (k-1 >= 0) dp[i][0][k] = dp[i-1][0][k-1]; // i桁目にnを選ぶ
            }
        }

        // N未満フラグ1への遷移
        for(ll k=0; k<K+1; k++) {
            if (n == 0) {
                dp[i][1][k] += dp[i-1][1][k]; // i桁目に0を選ぶ
                if (k-1 >= 0) dp[i][1][k] += dp[i-1][1][k-1]*9; // i桁目に[1,9]を選ぶ
            }
            else {
                dp[i][1][k] += dp[i-1][0][k] + dp[i-1][1][k]; // i桁目に0を選ぶ
                if (k-1 >= 0) {
                    dp[i][1][k] += dp[i-1][0][k-1]*(n-1); // i桁目に[1,n-1]を選ぶ
                    dp[i][1][k] += dp[i-1][1][k-1]*9; // i桁目に[1,9]を選ぶ
                }
            }
        }
    }

    // 答え
    ll ans = dp[D-1][0][K] + dp[D-1][1][K];
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}