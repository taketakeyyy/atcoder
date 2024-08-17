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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, X, Y; cin >> N >> X >> Y;
    // dp[i][a][b] := i番目の料理まで見て、甘さの総和がa、しょっぱさの総和がbのときの、食べた料理の最大数
    // ↑ O(NXY)でTLE
    // dp[i][a][v] := i番目の料理まで見て、甘さの総和がa、食べた料理の数がvのときの、しょっぱさの総和の最小値
    // ↑ O(XN^2)でOK
    const ll MAX_A = 10000;
    vector dp(MAX_A+1, vector(N+1, INF));
    dp[0][0] = 0;
    for(ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        // 選ばない場合
        auto olddp = dp; // 前回の状態引き継ぎ
        // 選ぶ場合
        for(ll preA=0; preA+a<=MAX_A; preA++) {
            for(ll v=0; v<N; v++) {
                if (olddp[preA][v] == INF) continue;
                chmin(dp[preA+a][v+1], olddp[preA][v]+b);
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll v=0; v<=N; v++) {
        for(ll a=0; a<=MAX_A; a++) {
            if (a<=X and dp[a][v]<=Y) {
                if (v < N) chmax(ans, v+1);
                else ans = N;
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}