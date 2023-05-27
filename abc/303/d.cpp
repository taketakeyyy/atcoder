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
    ll X, Y, Z; cin >> X >> Y >> Z;
    string S; cin >> S;

    ll N = S.size();
    // dp[i][j] := i番目のキーで、キャプスロックキーの状態がj(0:OFF, 1:ON)のときの、最短時間
    vector dp((ll)S.size()+1, vector<ll>(2, INF));
    if (S[0] == 'a') {
        dp[0][0] = X; // OFFのとき、ただX
        dp[0][1] = Z + Y; // ONのとき、Zでキャプスロックを切り替えてからY
    }
    else {
        dp[0][0] = Y; // OFFのとき、ただY
        dp[0][1] = Z + X; // ONのとき、Zでキャプスロックを切り替えてからX
    }
    for(ll i=1; i<(ll)S.size(); i++) {
        if (S[i] == 'a') {
            // OFFの場合
            ll t1 = dp[i-1][0] + X; // OFFの状態から、'a'をX秒で入力
            ll t2 = dp[i-1][1] + Z + X; // ONの状態から、Z秒でキャプスロックをOFFに切り替えてから、'a'をXで入力
            dp[i][0] = min(t1, t2);

            // ONの場合
            ll t3 = dp[i-1][0] + Z + Y;
            ll t4 = dp[i-1][1] + Y;
            dp[i][1] = min(t3, t4);
        }
        else {
            // OFFの場合
            ll t1 = dp[i-1][0] + Y;
            ll t2 = dp[i-1][1] + Z + Y;
            dp[i][0] = min(t1, t2);

            // ONの場合
            ll t3 = dp[i-1][0] + Z + X;
            ll t4 = dp[i-1][1] + X;
            dp[i][1] = min(t3, t4);
        }
    }

    ll ans = min(dp[N-1][0] , dp[N-1][1]);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}