#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define intceil(a, b) ((a + (b - 1)) / b)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long, long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x, y); }
void chmin(int& x, int y) { x = min(x, y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = {-1, 0, 1, 0};
vector<ll> vx = {0, 1, 0, -1};

#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;

// 解説AC
void solve() {
    ll N, A, B, P, Q;
    cin >> N >> A >> B >> P >> Q;

    // dp[i][j][f] := 高橋が地点i、青木が地点jにいて、次の手番がf(0:高橋, 1:青木)のときの高橋の勝率
    vector dp(N+1, vector<vector<mint>>(N+1, vector<mint>(2)));
    // 初期値を決める
    for(ll i=0; i<N; i++) {
        for(ll f=0; f<2; f++) {
            dp[N][i][f] = 1;
            dp[i][N][f] = 0;
        }
    }

    // dpの遷移
    for(ll i=N-1; i>=0; i--) {
        for(ll j=N-1; j>=0; j--) {
            // 高橋の移動
            for(ll k=1; k<=P; k++) {
                dp[i][j][0] += dp[min(N, i+k)][j][1];
            }
            dp[i][j][0] /= P;

            // 青木の移動
            for(ll k=1; k<=Q; k++) {
                dp[i][j][1] += dp[i][min(N, j+k)][0];
            }
            dp[i][j][1] /= Q;
        }
    }
    cout << dp[A][B][0].val() << endl;
}

int main() {
    solve();
    return 0;
}