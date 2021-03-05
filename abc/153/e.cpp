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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll H, N; cin >> H >> N;
    vector<ll> A, B;
    rep(i,N) {
        ll a, b; cin >> a >> b;
        A.push_back(a);
        B.push_back(b);
    }

    // dp間に合うのか？O(10^7)程度
    // dp[h] := ダメージをhにできる最小の魔力
    vector<ll> dp(H+1,INF);
    dp[0] = 0;
    for(int h=0; h<=H; h++) {
        for(int i=0; i<N; i++) {
            ll a = A[i];
            ll b = B[i];
            ll nh = min(H, h+a);
            dp[nh] = min(dp[nh], dp[h]+b);
        }
    }
    cout << dp[H] << endl;
}


int main() {
    solve();
    return 0;
}