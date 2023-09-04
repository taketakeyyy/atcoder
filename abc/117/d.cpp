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
    ll N; cin >> N;
    ll K; cin >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][j] := 上位i桁目まで見て、K未満フラグがjのときの、fの累積和の最大値
    vector dp(61, vector<ll>(2, 0));
    for(ll i=0; i<61; i++) {
        ll k = K>>(60-i)&1; // Kを2進数表記したときのi桁目の数字(0 or 1)

        // i桁目を0 or 1にしたときのfの値を求める
        ll total0 = 0;
        ll total1 = 0;
        for(ll n=0; n<N; n++) {
            ll a = A[n]>>(60-i)&1;  // A[n]を2進数表記したときのi桁目の数字(0 or 1)
            total0 += a^0;
            total1 += a^1;
        }
        total0 = total0<<(60-i);
        total1 = total1<<(60-i);

        if (i == 0) {
            // 未満フラグ0への遷移
            if (k == 0) {
                dp[i][0] = total0;
            }
            else {
                dp[i][0] = total1;
            }

            // 未満フラグ1への遷移
            if (k == 1) {
                dp[i][1] = total0;
            }
        }
        else {
            // 未満フラグ0への遷移
            if (k == 0) {
                dp[i][0] = dp[i-1][0]+total0;
            }
            else {
                dp[i][0] = max(dp[i-1][0]+total0, dp[i-1][0]+total1);
            }

            // 未満フラグ1への遷移
            if (dp[i-1][1] > 0) { // 0より大きいということは、未満フラグ1が立ったことがある
                dp[i][1] = max(dp[i-1][1]+total0, dp[i-1][1]+total1);
            }
            if (k == 1) {
                dp[i][1] = max(dp[i][1], dp[i-1][0]+total0);
            }
        }
    }

    // 答え
    ll ans = max(dp[60][0], dp[60][1]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}