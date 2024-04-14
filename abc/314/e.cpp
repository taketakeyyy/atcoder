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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> C(N), P(N);
    vector<vector<ll>> S(N);
    for(ll i=0; i<N; i++) {
        cin >> C[i] >> P[i];
        for(ll p=0; p<P[i]; p++) {
            ll a; cin >> a;
            S[i].push_back(a);
        }
    }

    // dp[i] := 現在持っているポイントがiのときの、終了するまでに必要な支払う金額の期待値
    vector<double> dp(10005, numeric_limits<double>::max());
    for(ll m=M; m<10005; m++) {
        dp[m] = 0;
    }
    for(ll m=M-1; m>=0; m--) {
        // ルーレットiを選ぶ
        for(ll i=0; i<N; i++) {
            double p = 1.0/P[i];
            double total = C[i];
            double cnt = 0; // 得られるポイントが0の個数
            for(ll j=0; j<P[i]; j++) {
                if (S[i][j] != 0) {
                    total += p * dp[m+S[i][j]];
                }
                else {
                    cnt += 1;
                }
            }
            double res = 1.0/(1.0-cnt*p) * total;
            dp[m] = min(dp[m], res);
        }
    }

    // 出力
    printf("%.10f\n", dp[0]);
}


int main() {
    solve();
    return 0;
}