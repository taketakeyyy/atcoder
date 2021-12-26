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
// const long long INF = LONG_LONG_MAX - 1001001001001001;
const long long INF = 1e18;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }

void solve() {
    ll N, X; cin >> N >> X;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 筆算の桁DP
    // dp[c] := (i桁目まで決めて、)繰り下がりがcのときの最小枚数
    vector<ll> dp(2, INF);
    dp[0] = 0;
    for(ll i=0; i<N-1; i++) {
        ll d = A[i+1]/A[i];  // 倍率
        ll x = X%d;  // Xのi桁目の値

        vector<ll> p(2, INF);
        swap(dp, p);  // pからdpへの遷移を書く
        for(ll c=0; c<2; c++) {  // i桁目の繰り下がり
            for(ll nc=0; nc<2; nc++) {  // i+1桁目の繰り下がり
                ll nx = x + c - nc*d;  // A[i]-B[i]の値。  今A[i]+B[i]の値が最小枚数にしたい。nxが正だったらA[i]に、負だったらB[i]にすればOK
                dp[nc] = min(dp[nc], p[c]+abs(nx));
            }
        }
        X /= d;
    }

    ll ans = INF;
    for(ll c=0; c<2; c++) {
        ans = min(ans, dp[c]+X+c);
    }
    cout << ans << endl;
}





int main() {
    solve();
    return 0;
}