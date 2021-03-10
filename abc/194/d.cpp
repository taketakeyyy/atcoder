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


int main() {
    solve();
    return 0;
}