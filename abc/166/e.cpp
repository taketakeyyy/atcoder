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
    // 式変形問題
    // j-i = Aj+Ai (i<j)を満たす個数を数えたい
    // j-Aj = i+Ai (i<j)を満たす個数を数えればよい
    // 上の式より、jとiは独立して考えられるようになった。
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    map<ll,ll> mp;
    ll ans = 0;
    // mapを更新しながら答えを数え上げていく(dpっぽい考え)
    // snuke式
    for(int i=0; i<N; i++) {
        ll li = i - A[i];
        ans += mp[li];
        ll ri = i + A[i];
        mp[ri]++;
    }
    cout << ans << endl;
}

void solve2() {
    // 式変形問題
    // j-i = Aj+Ai (i<j)を満たす個数を数えたい
    // j-Aj = i+Ai (i<j)を満たす個数を数えればよい
    // 上の式より、jとiは独立して考えられるようになった。
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    map<ll,ll> mp;
    ll ans = 0;
    // mapを更新しながら答えを数え上げていく
    // ナイーブな数え上げ(累積和っぽく書く)
    for(int i=1; i<N; i++) {
        // [0, i)までの累積和
        ll ri = (i-1) + A[i-1];
        mp[ri]++;

        // 条件を満たす個数を数え上げる
        ll li = i - A[i];
        ans += mp[li];
    }
    cout << ans << endl;
}

void solve3() {
    /* TLEだわ */
    // 式変形問題
    // j-i = Aj+Ai (i<j)を満たす個数を数えたい
    // j-Aj = i+Ai (i<j)を満たす個数を数えればよい
    // 上の式より、jとiは独立して考えられるようになった。
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    // ガチな累積和っぽく書く
    vector<map<ll,ll>> dp(N);  // dp[i] := i番目までのi+A[i]の個数
    dp[0][0+A[0]]++;
    for(int i=1; i<N; i++) {
        dp[i] = dp[i-1];
        dp[i][i+A[i]] = dp[i-1][i+A[i]] + 1;
    }

    // 数え上げる
    ll ans = 0;
    for(int i=1; i<N; i++) {
        ll li = i - A[i];
        ans += dp[i-1][li];
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}