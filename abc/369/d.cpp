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
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][j] := i番目まで見て、次に倒すときに2倍の経験値をもらえるかどうか(j)のときの、経験値の最大量
    vector<ll> dp(2, 0LL);
    dp[0] = 0;
    dp[1] = A[0];
    for(ll i=1; i<N; i++) {
        // 今回のモンスターを倒さない場合
        auto olddp = dp; // 引き継ぐ

        // 今回のモンスターを倒す場合
        chmax(dp[1], olddp[0]+A[i]);
        chmax(dp[0], olddp[1]+A[i]*2);
    }

    ll ans = -1;
    chmax(ans, dp[0]);
    chmax(ans, dp[1]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}