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


void solve1() {
    ll N, K; cin >> N >> K;
    vector<ll> A(K);
    for(ll i=0; i<=K-1; i++) {
        cin >> A[i];
    }

    // dp[i][j] := i（高橋or青木）のターンで、残りの石の個数がjのときの、そこからはじめたときの高橋の石の数
    vector dp(2, vector<ll>(N+1));
    for(ll j=1; j<=N; j++) {
        {  // 高橋のターン
            ll now = 0;
            for(ll a: A) {
                if (a <= j) now = max(now, dp[1][j-a]+a);
            }
            dp[0][j] = now;
        }
        {   // 青木のターン
            ll now = INF;
            for(ll a: A) {
                if (a <= j) now = min(now, dp[0][j-a]);
            }
            dp[1][j] = now;
        }
    }

    // 出力
    cout << dp[0][N] << endl;
}


int main() {
    solve1();
    // solve2();
    return 0;
}