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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

// 解説AC
// dp[i][s] := i袋作って、まだ使ってないアイテムの集合がsであるときの(x[i]-ave)^2の最小値
void solve() {
    ll N, D; cin >> N >> D;
    vector<ll> W(N);
    for(ll i=0; i<N; i++) cin >> W[i];

    // 平均を求める
    double ave = 0; // 平均
    for(ll i=0; i<N; i++) ave += W[i];
    ave /= D;

    // X[s] := 袋の中に入ってるアイテムの集合がsのときの、(x[i]-ave)^2の値
    vector<double> X(1<<N);
    for(ll s=0; s<(1<<N); s++) {
        for(ll d=0; d<N; d++) {
            if (s>>d&1) {
                X[s] += W[d];
            }
        }
        X[s] = (X[s]-ave)*(X[s]-ave);
    }

    // dp[i][s] := i袋作って、まだ使ってないアイテムの集合がsであるときの(x[i]-ave)^2の最小値
    const double INF = 1e18;
    vector<double> dp(1<<N, INF);
    dp[(1<<N)-1] = 0;
    for(ll i=0; i<D; i++) {
        vector<double> olddp(1<<N, INF);
        swap(olddp, dp);
        for(ll s=0; s<1<<N; s++) {
            for(ll t=s;; t=(t-1)&s) { // tは、sの部分集合だけを列挙したい
                // chmin(dp[1100], olddp[1111]+X[0011]);
                dp[s^t] = min(dp[s^t], olddp[s]+X[t]);
                if (t == 0) break;
            }
        }
    }
    double ans = dp[0]/D;
    printf("%.10lf\n", ans);
}


int main() {
    solve();
    return 0;
}