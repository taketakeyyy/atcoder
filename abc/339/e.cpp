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

#include <atcoder/segtree>
using S = long long;
S op(S a, S b) { return max(a, b); }
S e() { return -1; }
// max_rightの二分探索用
S target;
bool comp(S x) { return x < target; }

// セグ木
void solve() {
    ll N, D; cin >> N >> D;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][a] := i文字目まで見て、部分列の最後の値がaのときの、部分列の最長の長さ
    const ll MAX_A = 500000;
    vector dp(MAX_A+10,0LL);
    atcoder::segtree<S,op,e> seg(dp);
    for(ll i=0; i<N; i++) {
        ll a = A[i];
        ll l = max(1LL, a-D);
        ll r = min(MAX_A, a+D);
        ll v = seg.prod(l, r+1);
        seg.set(a, v+1);
    }

    // 答え
    ll ans = seg.prod(1LL, MAX_A+1);
    cout << ans << endl;
}

// TLE解法
void solve2() {
    ll N, D; cin >> N >> D;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // O(N^2)でTLE
    // dp[i][a] := i文字目まで見て、部分列の最後の値がaのときの、部分列の最長の長さ
    const ll MAX_A = 500000;
    vector dp(MAX_A+10,0LL);
    for(ll i=0; i<N; i++) {
        auto olddp = dp;
        ll a = A[i];
        ll l = max(1LL, a-D);
        ll r = min(MAX_A, a+D);
        for(ll j=l; j<=r; j++) { // [l,r]の範囲のmaxがdp[a]の値になる -> セグ木使える
            chmax(dp[a], olddp[j]+1);
        }
    }

    // 答え
    ll ans = 0;
    for(ll a=1; a<=MAX_A; a++) {
        chmax(ans, dp[a]);
    }
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}