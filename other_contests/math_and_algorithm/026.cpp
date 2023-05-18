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

// 漸化式のAC解法
void solve() {
    ll N; cin >> N;

    // dp[n] := n種類集めるのにかかる金額の期待値
    vector<double> dp(N+1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for(ll n=2; n<=N; n++) {
        double p = (double)(N-(n-1))/N; // 新しいのを引く確率
        dp[n] = dp[n-1] + 1.0/p;
    }
    printf("%.10f\n", dp[N]);
}

// ガチャコンプの公式
// 「新しいカードが出る回数の期待値は、新しいカードが出る確率の逆数」
// X0: 今0種類のコインを持っていて、新しい種類のコインが出るまでの金額
// Xn-1: 今n-1種類のコインを持っていて、新しい種類のコインが出るまでの金額
// E(X0+...+Xn-1) = E(X0) +...+ E(Xn-1)
void solve2() {
    ll N; cin >> N;

    double ans = 0;
    for(ll n=0; n<=N-1; n++) {
        ans += (double)N/(N-n);
    }
    printf("%.10f\n", ans);
}

int main() {
    // solve();
    solve2();
    return 0;
}