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
// const long long INF = 2e14+
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    string S; cin >> S;
    vector<ll> C(N);
    for(ll i=0; i<N; i++) cin >> C[i];

    // dp[i][j][k] := i文字目まで見て、すでに隣り合う文字が一致するものが存在するかどうか(j)で、今回の文字を反転させるかどうか(k)のときの、コストの最小値
    vector dp(2, vector(2, INF));
    dp[0][0] = 0;
    dp[0][1] = C[0];
    for(ll i=1; i<N; i++) {
        // S[i-1]とS[i]を比較する
        vector newdp(2, vector(2, INF));

        if (S[i-1]==S[i]) {
            // "00"
            chmin(newdp[1][0], dp[0][0]);      //"00"

            chmin(newdp[0][1], dp[0][0]+C[i]); //"01"
            chmin(newdp[1][1], dp[1][0]+C[i]); //"01"

            chmin(newdp[0][0], dp[0][1]);      //"10"
            chmin(newdp[1][0], dp[1][1]);      //"10"

            chmin(newdp[1][1], dp[0][1]+C[i]); //"11"
        }
        else {
            // "01"
            chmin(newdp[1][1], dp[0][0]+C[i]); //"00"

            chmin(newdp[0][0], dp[0][0]);      //"01"
            chmin(newdp[1][0], dp[1][0]);      //"01"

            chmin(newdp[0][1], dp[0][1]+C[i]); //"10"
            chmin(newdp[1][1], dp[1][1]+C[i]); //"10"

            chmin(newdp[1][0], dp[0][1]);      //"11"
        }
        swap(newdp, dp);
    }

    // 答え
    ll ans = min(dp[1][0], dp[1][1]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}