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
    ll W; cin >> W;
    ll N, K; cin >> N >> K;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    // dp[i][k][w] := スクショをi枚目まで見て、選んだのがk枚、合計幅wのときの合計重要度の最大値
    // このdpは直前の状態しか必要ないので、iは省略できる
    vector<vector<ll>> dp(K+1, vector<ll>(W+1, -1));
    dp[0][0] = 0;
    for(ll i=0; i<N; i++) {
        vector<vector<ll>> olddp(K+1, vector<ll>(W+1, -1));
        swap(olddp, dp);
        for(ll k=0; k<=K; k++) {
            for(ll w=0; w<=W; w++) {
                // i枚目のスクショを選ばない場合
                dp[k][w] = max(dp[k][w], olddp[k][w]);
                // i枚目のスクショを選んだ場合
                if (k+1<=K && w+A[i]<=W && olddp[k][w]!=-1) {
                    dp[k+1][w+A[i]] = max(dp[k+1][w+A[i]], olddp[k][w]+B[i]);
                }
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll k=0; k<=K; k++) {
        for(ll w=0; w<=W; w++) {
            ans = max(ans, dp[k][w]);
        }
    }
    cout << ans << endl;
}

void solve2() {
    ll W; cin >> W;
    ll N, K; cin >> N >> K;
    vector<ll> A(N+1), B(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i] >> B[i];
    }

    // dp[i][k][w] := スクショをi枚目まで見て、選んだのがk枚、合計幅wのときの合計重要度の最大値
    vector dp(N+1, vector<vector<ll>>(K+1, vector<ll>(W+1, -1)));
    dp[0][0][0] = 0;
    for(ll i=1; i<=N; i++) {
        for(ll k=0; k<=K; k++) {
            for(ll w=0; w<=W; w++) {
                // i枚目のスクショを選ばない場合
                dp[i][k][w] = max(dp[i][k][w], dp[i-1][k][w]);
                // i枚目のスクショを選ぶ場合
                if (k-1>=0 && w-A[i]>=0 && dp[i-1][k-1][w-A[i]]!=1) {
                    dp[i][k][w] = max(dp[i][k][w], dp[i-1][k-1][w-A[i]]+B[i]);
                }
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll k=0; k<=K; k++) {
        for(ll w=0; w<=W; w++) {
            ans = max(ans, dp[N][k][w]);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    // solve2();
    return 0;
}