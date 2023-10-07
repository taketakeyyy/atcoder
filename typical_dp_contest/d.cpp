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


// AC
// O(N^4)だが、ACする
void solve() {
    ll N, D; cin >> N >> D;

    // Dの素因数を得る
    map<ll,ll> mp; // 素因数格納
    while(D%2 == 0) {
        D /= 2;
        mp[2]++;
    }
    while(D%3 == 0) {
        D /= 3;
        mp[3]++;
    }
    while(D%5 == 0) {
        D /= 5;
        mp[5]++;
    }
    if (D != 1) { // {2,3,5}以外の素因数を持つならば、サイコロを振ってDの倍数を作ることができない
        cout << 0 << endl;
        return;
    }

    // O(N^4)
    // dp[i][a][b][c] := サイコロをi回降ったときの、2の素因数がa個、3の素因数がb個、5の素因数がc個になる確率
    const static double p = 1.0/6.0;
    vector dp(2*N+1, vector<vector<double>>(N+1, vector<double>(N+1, 0)));
    dp[0][0][0] = 1.0;
    for(ll i=0; i<N; i++) { // max.100
        vector newdp(2*N+1, vector<vector<double>>(N+1, vector<double>(N+1, 0)));
        for(ll a=0; a<=2*N; a++) { // max.200
            for(ll b=0; b<=N; b++) { // max.100
                for(ll c=0; c<=N; c++) { // max.100
                    // 1が出た場合
                    newdp[a][b][c] += dp[a][b][c]*p;
                    // 2が出た場合
                    if (a+1 <= 2*N) newdp[a+1][b][c] += dp[a][b][c]*p;
                    // 3が出た場合
                    if (b+1 <= N) newdp[a][b+1][c] += dp[a][b][c]*p;
                    // 4が出た場合
                    if (a+2 <= 2*N) newdp[a+2][b][c] += dp[a][b][c]*p;
                    // 5が出た場合
                    if (c+1 <= N) newdp[a][b][c+1] += dp[a][b][c]*p;
                    // 6が出た場合
                    if (a+1<=2*N && b+1<=N) newdp[a+1][b+1][c] += dp[a][b][c]*p;
                }
            }
        }
        dp = newdp;
    }

    // 答え
    double ans = 0;
    for(ll a=mp[2]; a<=2*N; a++) {
        for(ll b=mp[3]; b<=N; b++) {
            for(ll c=mp[5]; c<=N; c++) {
                ans += dp[a][b][c];
            }
        }
    }
    printf("%.10f\n", ans);
}


// 解説AC
// 100回連続で4の目が出たら、2の素因数は200個になる。
// しかし、Dの最大値は10^18である。これは2^64以下である。
// よって、2の倍数の個数は64以下にまとめてよい。3,5の倍数も同様。
// これで計算量が落とせる。
void solve2() {
    ll N, D; cin >> N >> D;

    // Dの素因数を得る
    map<ll,ll> mp; // 素因数格納
    while(D%2 == 0) {
        D /= 2;
        mp[2]++;
    }
    while(D%3 == 0) {
        D /= 3;
        mp[3]++;
    }
    while(D%5 == 0) {
        D /= 5;
        mp[5]++;
    }
    if (D != 1) { // {2,3,5}以外の素因数を持つならば、サイコロを振ってDの倍数を作ることができない
        cout << 0 << endl;
        return;
    }

    // O(N^4)
    // dp[i][a][b][c] := サイコロをi回降ったときの、2の素因数がa個、3の素因数がb個、5の素因数がc個になる確率
    const static double p = 1.0/6.0;
    vector dp(65, vector<vector<double>>(65, vector<double>(65, 0)));
    dp[0][0][0] = 1.0;
    for(ll i=0; i<N; i++) { // max.100
        vector newdp(65, vector<vector<double>>(65, vector<double>(65, 0)));
        for(ll a=0; a<=64; a++) { // max.64
            for(ll b=0; b<=64; b++) { // max.64
                for(ll c=0; c<=64; c++) { // max.64
                    // 1が出た場合
                    newdp[a][b][c] += dp[a][b][c]*p;
                    // 2が出た場合
                    if (a+1 <= 64) newdp[a+1][b][c] += dp[a][b][c]*p;
                    else newdp[a][b][c] += dp[a][b][c]*p;
                    // 3が出た場合
                    if (b+1 <= 64) newdp[a][b+1][c] += dp[a][b][c]*p;
                    else newdp[a][b][c] += dp[a][b][c]*p;
                    // 4が出た場合
                    if (a+2 <= 64) newdp[a+2][b][c] += dp[a][b][c]*p;
                    else newdp[a][b][c] += dp[a][b][c]*p;
                    // 5が出た場合
                    if (c+1 <= 64) newdp[a][b][c+1] += dp[a][b][c]*p;
                    else newdp[a][b][c] += dp[a][b][c]*p;
                    // 6が出た場合
                    if (a+1<=64 && b+1<=64) newdp[a+1][b+1][c] += dp[a][b][c]*p;
                    else if (a+1<=64) newdp[a+1][b][c] += dp[a][b][c]*p;
                    else if (b+1<=64) newdp[a][b+1][c] += dp[a][b][c]*p;
                    else newdp[a][b][c] += dp[a][b][c]*p;
                }
            }
        }
        dp = newdp;
    }

    // 答え
    double ans = 0;
    for(ll a=mp[2]; a<=64; a++) {
        for(ll b=mp[3]; b<=64; b++) {
            for(ll c=mp[5]; c<=64; c++) {
                ans += dp[a][b][c];
            }
        }
    }
    printf("%.10f\n", ans);
}


int main() {
    // solve();
    solve2();
    return 0;
}