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


// [考察1]
// A = 53421, K = 2 とする
// まず、上位桁の数字を一致させるのが差を小さくする上で最優先事項。。。というわけではない
// A = 800000, K = 1
// A' = 777777 が最適。

// [考察2]
// A = 53421, K = 2 とする
// A' = 53??? までは確定したとする。
// 次は何の値を入力すべき？
// (1) A' = 535??のとき（Aより大きいことが確定したとき）
// これ以降はすべて最小の値を入力するのが、Aとの差を最小にする最適な方法（A'=53533）
// (2) A' = 533??のとき（Aより小さいことが確定したとき）
// これ以降はすべて最大の値を入力するのが、Aとの差を最小にする最適な方法（A'=53355）

// AC
// 桁DP解
void solve() {
    ll A, K; cin >> A >> K;
    string SA = to_string(A);
    ll SASZ = SA.size();

    // 上位桁から埋めていく。
    // dp[i][state][k] := i桁目まで見て、使った数の集合がstateで、大小フラグがk(0:Aと同じ,1:Aより小さい,2:Aより大きい)のときの、Aに最も近い整数
    vector dp(SASZ+1, vector<vector<ll>>(1<<10, vector<ll>(3, -1)));
    dp[0][0][0] = 0;
    for(ll i=0; i<SASZ; i++) {
        ll a = SA[i]-'0'; // i桁目のAの数字

        for(ll state=0; state<(1<<10); state++) {
            for(ll k=0; k<3; k++) {
                if (dp[i][state][k] == -1) continue;

                // 数字dを使う
                for(ll d=0; d<10; d++) {
                    ll nstate = state | (1<<d);

                    // nstateのビットが立っている数はK以下か？
                    ll cnt = 0;
                    for(ll j=0; j<10; j++) if(state>>j&1) cnt++;
                    if (cnt > K) continue;

                    // nstateで桁が1の中からどれを選ぶのが最適か？
                    if (k == 0) {
                        // Aと同じとき

                        // Aと同じものを選ぶ遷移
                        if (nstate>>a&1) dp[i+1][nstate][0] = dp[i][state][k]*10+a;

                        // Aより小さいものを選ぶ遷移
                        for(ll l=0; l<a; l++) {
                            if (nstate>>l&1) {
                                if (dp[i+1][nstate][1] == -1) dp[i+1][nstate][1] = dp[i][state][k]*10+l;
                                else { // Aより小さいことが確定しているとき、できるだけ値を大きくするのがAとの差が小さくなるので最適
                                    dp[i+1][nstate][1] = max(dp[i+1][nstate][1], dp[i][state][k]*10+l);
                                }
                            }
                        }

                        // Aより大きいものを選ぶ遷移
                        for(ll l=9; l>a; l--) {
                            if (nstate>>l&1) {
                                if (dp[i+1][nstate][2] == -1) dp[i+1][nstate][2] = dp[i][state][k]*10+l;
                                else { // Aより大きいことが確定しているとき、できるだけ値を小さくするのがAとの差が小さくなるので最適
                                    dp[i+1][nstate][2] = min(dp[i+1][nstate][2], dp[i][state][k]*10+l);
                                }
                            }
                        }
                    }
                    else if (k == 1) {
                        // Aより小さいとき
                        for(ll l=0; l<10; l++) {
                            if (nstate>>l&1) {
                                dp[i+1][nstate][1] = max(dp[i+1][nstate][1], dp[i][state][k]*10+l);
                            }
                        }
                    }
                    else if (k == 2) {
                        // Aより大きいとき
                        for(ll l=9; l>=0; l--) {
                            if (nstate>>l&1) {
                                if (dp[i+1][nstate][2] == -1) dp[i+1][nstate][2] = dp[i][state][k]*10+l;
                                dp[i+1][nstate][2] = min(dp[i+1][nstate][2], dp[i][state][k]*10+l);
                            }
                        }
                    }
                }
            }
        }
    }

    // 答え
    ll ans = INF;
    for(ll state=0; state<1<<10; state++) {
        for(ll k=0; k<3; k++) {
            ll cnt = 0;
            for(ll j=0; j<10; j++) if(state>>j&1) cnt++;
            if (cnt > K) continue;
            if (dp[SASZ][state][k]==-1) continue;
            ans = min(ans, abs(dp[SASZ][state][k]-A));
        }
    }
    // A=100、K=1のとき、099も実はありえる入力（先頭の0は入力しない扱い）
    ll r = 0;
    for(ll i=0; i<SASZ-1; i++) {
        r*=10; r+=9;
    }
    ans = min(ans, abs(A-r));
    cout << ans << endl;
}


// https://qiita.com/ophhdn/items/339133a31b9e33c8c264
// 近似させる数を桁ごとにみると、[元の数字と同じ部分(n桁)] + [元の数字と違う数字1桁（1~9のいずれか）] + [残りの桁は全て同じ数字]、という構成になることがわかる。
//
// 一度違う数字を使うと、それより下の桁でいかなる数字を使おうとも元の数字より大きい or 小さいは既に決定している。したがって、使える数字の中から最も小さい or 大きい数字を使い続けるのが最も元の数に近い数となる。
//
// どこの桁で初めて元の数字と違う数が出現するかで15通り、初めて出現する違う数10通り、残りの桁の全てで使う数で10通り。
void solve2() {
    ll A, K; cin >> A >> K;
    string SA = to_string(A);
    ll SASZ = SA.size();

}

int main() {
    solve();
    // solve2();
    return 0;
}