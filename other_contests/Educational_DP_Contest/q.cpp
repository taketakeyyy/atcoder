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


// WA解法
void solve() {
    ll N; cin >> N;
    vector<ll> H(N), A(N);
    for(ll i=0; i<N; i++) cin >> H[i];
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][j] := 左からi番目の花まで見て、右端の高さがjのときの美しさの総和の最大値 O(N^2)
    vector dp(N, vector<ll>(N+1, -1));
    // 初期状態
    dp[0][0] = 0;
    dp[0][H[0]] = A[0];
    // DPうめる
    for(ll i=1; i<N; i++) {
        for(ll j=0; j<=N; j++) {
            // i番目の花を抜く場合
            dp[i][j] = max(dp[i][j], dp[i-1][j]);

            // i番目の花を抜かない場合
            if (H[i] > j) {
                dp[i][H[i]] = max(dp[i][H[i]], dp[i-1][j]+A[i]);
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll j=0; j<=N; j++) ans = max(ans, dp[N-1][j]);
    cout << ans << endl;
}


// AC
// dp[i][H[i]] の一箇所しか更新されない
// さらに dp[i][H[i]] は、j < H[i] の (dp[i-1][j] の中の最大値) + A[i] なので、区間最大値取得を使えれば高速にdp[i][H[i]]を求められる
// これはセグメントツリーを使えばよい
#include <atcoder/segtree>
using S = long long;
S op(S a, S b) { return max(a, b); }
S e() { return -1; }

void solve2() {
    ll N; cin >> N;
    vector<ll> H(N), A(N);
    for(ll i=0; i<N; i++) cin >> H[i];
    for(ll i=0; i<N; i++) cin >> A[i];


    // dp[j] := 右端の高さがjのときの美しさの総和の最大値 O(NlogN)
    vector<ll> dp(N+1, 0);
    // 初期状態
    dp[0] = 0;
    dp[H[0]] = A[0];
    atcoder::segtree<S, op, e> seg(dp); // dpをセグ木にのせる
    // DPうめる
    for(ll i=1; i<N; i++) {
        // i番目の花を抜かない場合
        dp[H[i]] = max(dp[H[i]], seg.prod(0, H[i])+A[i]);
        seg.set(H[i], dp[H[i]]);
    }

    // 答え
    ll ans = 0;
    for(ll i=0; i<N+1; i++) ans = max(ans, dp[i]);
    cout << ans << endl;

}

int main() {
    // solve();
    solve2();
    return 0;
}