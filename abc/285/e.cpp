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


// 解説AC
// 円環状の問題を解く場合、特別な意味のあるものを先頭に固定するのが定石らしい。
// 今回は曜日1を「休日」に固定することがそれにあたる。
// (1) B[i] := 休日同士の間にi個平日があるときの、合計生産量 を作る
// (2) dp[i][j] := i曜日まで割当を決めて、現在連続している平日の数がjのときの、生産量の最大値
// 以上のステップで解ける
// (疑問)曜日1で「休日」固定でいいの？曜日2とか3とかを「休日」にするパターンがあるじゃん？
// ある曜日の生産量は曜日によらない。「休日」なら0、「平日」なら「直近の休日」によって決まる。
// 配列Aは曜日に対応しているわけではないのに注意しよう。
void solve() {
    ll N; cin >> N;
    vector<ll> A(N+1);
    for(ll i=1; i<N+1; i++) cin >> A[i];
    vector<ll> B(N+1, 0);  // B[i] := 休日同士の間にi個平日があるときの、合計生産量
    for(ll i=1; i<N+1; i++) {
        B[i] = B[i-1] + A[(i+1)/2];
    }

    // dp[i][j] := i曜日まで割当を決めて、現在連続している平日の数がjのときの、生産量の最大値
    vector dp(N+1, vector<ll>(N+1, -1));
    dp[1][0] = 0;  // 曜日1を休日に固定(1-indexed)
    for(ll i=1; i<N; i++) {
        // i+1曜日を「休日」固定で考える?
        for(ll j=0; j<=N; j++) {
            if (dp[i][j] == -1) continue;
            // i曜日を「平日」にする場合
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
            // i曜日を「休日」にする場合
            dp[i+1][0] = max(dp[i+1][0], dp[i][j] + B[j]);
        }
    }

    // 最終的な答え
    ll ans = 0;
    for(ll j=0; j<N; j++) {
        ans = max(ans, dp[N][j] + B[j]);
    }
    cout << ans << endl;
}

// 解説動画
void solve2() {
    ll N; cin >> N;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) cin >> A[i];
    vector<ll> B(N+1);  // B[i] := 休日同士の間にi個平日があるときの、合計生産量
    for(ll w=0; w<N+1; w++) {  // 幅
        for(ll i=1; i<w; i++) {
            ll j = w-i;
            B[w] += A[min(i,j)];
        }
    }

    vector<ll> dp(N+1);
    for(ll i=1; i<=N; i++) {
        for(ll j=0; j<i; j++) {
            dp[i] = max(dp[i], dp[j]+B[i-j]);
        }
    }
    cout << dp[N] << endl;
}


// dp[i] := i曜日が「休日」であるときの、i曜日までの総生産量の最大値
void solve3() {
    ll N; cin >> N;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) cin >> A[i];
    vector<ll> B(N+1, 0);  // B[i] := 休日同士の間にi個平日があるときの、合計生産量
    for(ll i=1; i<N+1; i++) {
        B[i] = B[i-1] + A[(i+1)/2];
    }

    // dp[i] := i曜日が「休日」であるときの、i曜日までの総生産量の最大値
    vector<ll> dp(N+1, 0);  // N曜日も作り、0曜日とN曜日を「休日」に固定する
    dp[0] = 0;
    for(ll i=1; i<=N; i++) {
        for(ll j=0; j<=i-1; j++) {
            dp[i] = max(dp[i], dp[j]+B[i-1-j]);
        }
    }
    cout << dp[N] << endl;
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}