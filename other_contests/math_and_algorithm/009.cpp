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
    ll N, S; cin >> N >> S;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[a] := 合計がaになるかどうか
    const ll MAX_A = 60*10000;
    vector<bool> dp(MAX_A+1, false);
    dp[0] = true;
    for(ll i=0; i<N; i++) {
        auto olddp = dp;
        for(ll a=0; a<=MAX_A; a++) {
            if (a+A[i] > MAX_A) break;
            if (olddp[a]) dp[a+A[i]] = true;
        }
    }

    // 出力
    if (dp[S]) cout << "Yes" << endl;
    else cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}