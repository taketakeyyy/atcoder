#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N+1);
    for(ll i=1; i<N+1; i++) {
        cin >> A[i];
    }

    // dp[i][j] := 左からi番目までを見て、j個選んだときのスコアの最大値
    vector dp(N+1, vector<ll>(M+1, -INF));
    dp[1][1] = A[1];
    for(ll i=2; i<=N; i++) {
        dp[i][1] = max(dp[i-1][1], A[i]);
    }
    for(ll i=2; i<=N; i++) {
        for(ll j=2; j<=M; j++) {
            if (j > i) break;
            dp[i][j] = max(dp[i][j], dp[i-1][j]);  // 選ばない
            dp[i][j] = max(dp[i][j], dp[i-1][j-1] + j*A[i]);  // 選んだ
        }
    }
    cout << dp[N][M] << endl;
}


int main() {
    solve();
    return 0;
}