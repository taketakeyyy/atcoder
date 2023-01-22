#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
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


// Aの各要素はM以下であり、Aの合計がK以下になるような数列Aは何通り？
void solve() {
    ll N, M, K; cin >> N >> M >> K;

    // dp[i][sum] := i番目までの要素を足して、合計値がsumになるような場合の数
    vector dp(N+1, vector<ll>(K+1, 0));
    dp[0][0] = 1;
    for(ll i=1; i<=N; i++) {
        for(ll sum=0; sum<=K; sum++) {
            for(ll a=1; a<=M; a++) {
                if (sum-a < 0) break;
                dp[i][sum] += dp[i-1][sum-a];
                dp[i][sum] %= MOD;
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll sum=0; sum<=K; sum++) {
        ans += dp[N][sum];
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}