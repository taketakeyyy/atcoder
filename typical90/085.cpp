#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve() {
    ll K; cin >> K;

    // abc=K (a<=b<=c)より、aはたかだかKの3乗根
    ll ans = 0;
    for(ll a=1; a*a*a<=K; a++) {  // たかだか10^4ステップ
        if (K%a!=0) continue;
        ll K2 = K/a;
        for(ll b=a; b*b<=K2; b++) {  // a=10^4のとき、b=10^4ステップ / a=1のとき、b=10^6ステップ
            if (K2%b!=0) continue;
            ans++;
        }
    }

    // 答えを出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}