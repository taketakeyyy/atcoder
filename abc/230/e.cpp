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
    // 入力
    ll N; cin >> N;

    // √Nの上下で分ける:https://twitter.com/kyopro_friends/status/1466766241839075328
    // 答えを計算
    ll ans = 0;
    // √N以下の場合
    ll j;
    for(ll i=1; i*i<=N; i++) {
        ans += N/i;
        j = i;
    }
    // √Nより大きい場合
    for(ll i=j+1; i<=N; i++) {
        ll k = N/i;
        ll cnt = N/k - N/(k+1);
        ans += k*cnt;
        i += cnt-1;
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}