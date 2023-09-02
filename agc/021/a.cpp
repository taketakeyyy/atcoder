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

    // dp[i][j] := 左からi桁目まで見て、未満フラグがjのときの、各桁の和の最大値
    vector dp(N.size(), vector<ll>(2, 0));
    // 0桁目の初期値を埋める
    dp[0][0] = N[0]-'0';
    dp[0][1] = (N[0]-'0')-1;
    // dpを埋める
    for(ll i=1; i<(ll)N.size(); i++) {
        ll n = N[i]-'0'; // Nのi桁目の数字

        // 未満フラグが0への遷移
        dp[i][0] = dp[i-1][0] + n; // 未満フラグが0からは、nを足すのが最適
                                   // 未満フラグが1からの遷移は存在しない

        // 未満フラグが1への遷移
        if (n > 0) {
            ll ret1 = dp[i-1][0]+(n-1); // 未満フラグを立たせるには、n-1を足すのが最適
            ll ret2 = dp[i-1][1]+9; // 未満フラグがすでに立っているときは、9を足すのが最適
            dp[i][1] = max(ret1, ret2);
        }
        else {
            dp[i][1] = dp[i-1][1]+9;
        }
    }

    // 答え
    ll ans = max(dp[N.size()-1][0], dp[N.size()-1][1]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}