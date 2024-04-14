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
    ll N; cin >> N;
    // 「有効なのが来るまでカードを引く回数の期待値は、有効なカードを引く確率の逆数」
    // N個の頂点があるとき、
    // (1) 残りのN-1個のどれかを選ぶ確率の期待値は、N/N-1
    // (2) 残りのN-2個のどれかを選ぶ確率の期待値は、N/N-2
    // ...
    // (N-1) 残りの1個のどれかを選ぶ確率の期待値は、N/1
    // 期待値の線形性より、各期待値を足し合わせたものが答え
    double ans = 0;
    for (ll i=1; i<=N-1; i++) {
        ans += (double)N/i;
    }
    printf("%.10lf\n",ans);
}

// AC
void solve2() {
    ll N; cin >> N;

    // 現在n個の頂点が連結している状態での、終了するまでの操作回数の期待値dp[n]
    vector<double> dp(N+1);
    dp[N] = 0;
    for(ll n=N-1; n>=1; n--) {
        dp[n] = dp[n+1] + (double)N/(N-n);
    }
    printf("%.10lf\n",dp[1]);
}

// WA
// solve2のように「終了するまでの」操作回数の期待値としないと、うまく動かないんだよなあ。理由はあまりわかってない。
void solve3() {
    ll N; cin >> N;

    // 現在n個の頂点が連結している状態になるまでの、操作回数の期待値dp[n]
    vector<double> dp(N+1);
    dp[1] = 0;
    for(ll n=1; n<=N-1; n++) {
        dp[n+1] = dp[n] - (double)N/(N-n);
    }
    printf("%.10lf\n",dp[N]);
}

int main() {
    // solve();
    solve2();
    // solve3();
    return 0;
}