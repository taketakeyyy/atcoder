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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// dp[x] := x段目にいくことができるか？
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    ll M; cin >> M;
    vector<ll> B(M);
    for(ll i=0; i<M; i++) cin >> B[i];
    ll X; cin >> X;
    vector<bool> mochi(X+1, false);
    for(ll i=0; i<M; i++) mochi[B[i]] = true;

    // dp[x] := x段目に行くことができるか？
    vector<bool> dp(X+1, false);
    dp[0] = true;
    for(ll i=0; i<X+1; i++) {
        if (!dp[i]) continue;
        if (mochi[i]) continue;
        for(ll j=0; j<N; j++) {
            if (i+A[j] > X) continue;
            dp[i+A[j]] = true;
        }
    }

    if (dp[X]) cout << "Yes" << endl;
    else cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}