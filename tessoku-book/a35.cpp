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
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][j] := お互いが最適な行動をしたときの、i行j列目のスコア
    vector dp(N, vector<ll>(0));
    dp[N-1] = A;  // N-1行目は、明らかにAと同じ
    for(ll i=N-2; i>=0; i--) {  // ピラミッドの下から埋めていく
        dp[i].resize(i+1);
        for(ll j=0; j<i+1; j++) {
            if (i%2==0) {
                // 太郎の手番
                dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]);
            }
            else {
                // 次郎の手番
                dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]);
            }
        }
    }

    // 出力
    cout << dp[0][0] << endl;
}


int main() {
    solve();
    return 0;
}