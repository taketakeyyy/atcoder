#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N, B, K; cin >> N >> B >> K;
    vector<ll> C(K);
    for(int i=0; i<K; i++) cin >> C[i];

    // MODの世界の桁DP
    // dp[n] := 整数nを作ることができる場合の数
    vector<ll> dp(B, 0);
    dp[0] = 1;

    ll base = 1;
    for(int i=0; i<N; i++) {
        vector<ll> old = dp;
        fill(dp.begin(), dp.end(), 0);

        for(int k=0; k<K; k++) {
            ll c = C[k] * base; c %= B;
            for(int j=0; j<B; j++) {
                dp[(j+c)%B] += old[j];
                dp[(j+c)%B] %= MOD;
            }
        }
        base *= 10; base %= B;
    }

    // 出力
    cout << dp[0] << endl;
}


int main() {
    solve();
    return 0;
}