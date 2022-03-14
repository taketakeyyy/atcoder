#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[k] := 新しく作られた値がkとなる操作手順の場合の数
    vector<ll> dp(10, 0);
    dp[(A[0]+A[1])%10] += 1;
    dp[(A[0]*A[1])%10] += 1;
    for(ll i=2; i<N; i++) {
        vector<ll> old(10, 0);
        swap(old, dp);
        for(ll k=0; k<=9; k++) {
            dp[(A[i]+k)%10] += (old[k]) % MOD;
            dp[(A[i]+k)%10] %= MOD;
            dp[(A[i]*k)%10] += (old[k]) % MOD;
            dp[(A[i]*k)%10] %= MOD;
        }
    }

    // 出力
    for(ll k=0; k<=9; k++) {
        cout << (dp[k])%MOD << endl;
    }
}


int main() {
    solve();
    return 0;
}