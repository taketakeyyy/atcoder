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
    vector<ll> X(N), Y(N), Z(N);
    vector<ll> XX, YY, ZZ; // 高橋が負けてる区のX,Y,Z
    ll taka = 0; // 高橋の議席
    ll total = 0; // 全議席
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i] >> Z[i];
        total += Z[i];

        if (X[i] > Y[i]) {
            taka += Z[i];
        }
        else {
            XX.push_back(X[i]);
            YY.push_back(Y[i]);
            ZZ.push_back(Z[i]);
        }
    }

    // dp[i][j] := 左からi番目まで見て、議席数がjのときの、鞍替えさせた人数の最小値
    ll NN = XX.size();
    vector dp(1e5+1, INF);
    for(ll j=0; j<1e5+1; j++) {
        if (j <= taka) {
            dp[j] = 0;
        }
    }
    for(ll i=0; i<NN; i++) {
        auto olddp = dp;
        // i番目の区を奪う場合
        for(ll j=0; j<1e5+1; j++) {
            if (j-ZZ[i] >= 0) {
                ll cost = intceil(YY[i]-XX[i], 2);
                dp[j] = min(dp[j], olddp[j-ZZ[i]] + cost);
            }
        }
    }

    // 答え
    ll ans = INF;
    for(ll j=intceil(total,2); j<1e5+1; j++) {
        ans = min(ans, dp[j]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}