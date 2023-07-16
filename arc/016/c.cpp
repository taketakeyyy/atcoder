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
    vector<ll> cost(M); // cost[i] := くじiの料金
    vector<vector<pair<ll,double>>> lotte(M); // lotte[i] := くじiの(アイドル,出現確率)のリスト
    for(ll i=0; i<M; i++) {
        ll C, cst; cin >> C >> cst;
        cost[i] = cst;
        for(ll c=0; c<C; c++) {
            ll idol, p; cin >> idol >> p;
            lotte[i].push_back({idol-1, (double)p/100});
        }
    }

    // bitDPで降順に埋める
    // dp[bit] := 現在所持するアイドルの状態がbitのときの、終了するまでに必要な金額の期待値
    vector<double> dp(1<<N, 0);
    dp[(1<<N)-1] = 0.0;
    for(ll bit=(1<<N)-2; bit>=0; bit--) {
        // dp[bit]を求めたい
        dp[bit] = std::numeric_limits<double>::max();
        // くじmを使ったときの期待値をそれぞれm個求めて、そのうちの最小のものが最適な戦略なので、期待値dp[bit]になる
        for(ll m=0; m<M; m++) { // くじm
            double expect = cost[m]; // くじmを使ったときの期待値
            double stag = 0; // dp[bit]に停滞する確率
            for(auto [idol, p]: lotte[m]) {
                if (bit>>idol&1) {
                    stag += p;
                }
                else {
                    expect += p*dp[bit|(1<<idol)];
                }
            }
            if (1.0-stag <= 0.0) continue; // doubleの比較は誤差が怖いので == ではなく <= を使う
            expect /= (1.0-stag);
            dp[bit] = min(dp[bit], expect);
        }
    }
    printf("%.10lf\n", dp[0]);
}


int main() {
    solve();
    return 0;
}