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
// この解法の場合、
//     d: 01234
// state: 11111 という状況の場合、最初に1にボールを投げるが、それは本当に正しいか？
void solve() {
    ll N; cin >> N;
    ll S = 0; // ものが置いてある座標を2進数で保持
    for(ll i=0; i<N; i++) {
        ll x; cin >> x;
        x++;
        S |= (1<<x);
    }

    // f(state) := 現在、ものが置かれている座標がstateである状態の、終了するまでにボールを投げる回数の期待値
    vector<double> memo(1<<18, -1.0);
    memo[0] = 0;
    auto f = [&](auto self, ll state) -> double {
        if (memo[state] >= 0) return memo[state];

        // dp遷移(連続する3つのビットに注目する)
        // 3つ連続してものがある場合、その真中にボールを投げるのが最適
        {
            ll seq = 0;
            for(ll d=0; d<18; d++) {
                if (state>>d&1) seq++;
                else seq = 0;
                if (seq == 3) {
                    // (d,d-1,d-2)の3本が立っている
                    double p = 1.0/3; // 遷移確率
                    memo[state] = 1;
                    memo[state] += p*self(self, state^(1<<d));
                    memo[state] += p*self(self, state^(1<<(d-1)));
                    memo[state] += p*self(self, state^(1<<(d-2)));
                    return memo[state];
                }
            }
        }

        // 2つビットが立っている場合、その真中に向けてボールを投げるのが最適
        {
            for(ll d=1; d<17; d++) {
                ll num = 0; // 立っているビットの数
                num += state>>(d-1)&1;
                num += state>>d&1;
                num += state>>(d+1)&1;

                if (num == 2) {
                    // 今、(d-1,d,d+1)のうち2つのビットが立っている
                    double p = 1.0/3; // 遷移確率
                    memo[state] = 1;
                    if (state>>(d-1)&1) memo[state] += p*self(self, state^(1<<(d-1)));
                    if (state>>d&1) memo[state] += p*self(self, state^(1<<d));
                    if (state>>(d+1)&1) memo[state] += p*self(self, state^(1<<(d+1)));
                    return memo[state] *= 3.0/2.0;
                }
            }
        }

        // 1つだけポツンと立っている場合、ものに向けてボールを投げるのが最適
        {
            for(ll d=0; d<18; d++) {
                if (state>>d&1) {
                    return memo[state] = 3 + self(self, state^(1<<d));
                }
            }
        }

        // どのビットも立っていない
        return memo[0];
    };

    printf("%.16f\n", f(f, S));
}


// AC解法
// 「最適行動」は自分で考えず、最小（最大）を採用するようにしたほうがよい。
void solve2() {
    ll N; cin >> N;
    ll S = 0; // ものが置いてある座標を2進数で保持
    for(ll i=0; i<N; i++) {
        ll x; cin >> x;
        x++;
        S |= (1<<x);
    }

    // f(state) := 現在、ものが置かれている座標がstateである状態の、終了するまでにボールを投げる回数の期待値
    vector<double> memo(1<<18, -1.0);
    memo[0] = 0;
    auto f = [&](auto self, ll state) -> double {
        if (memo[state] >= 0) return memo[state];

        // d=[1,16]箇所にボールを投げて、最も期待値の小さいところを採用する
        double ret = numeric_limits<double>::max();
        for(ll d=1; d<=16; d++) {
            // 連続する3つのビット(d-1,d,d+1)に注目する
            ll num = 0; // 立っているビットの数
            num += state>>(d-1)&1;
            num += state>>d&1;
            num += state>>(d+1)&1;

            if (num == 3) {
                // (d-1,d,d+1)の3本が立っている
                double p = 1.0/3; // 遷移確率
                double expect = 1; // 期待値
                expect += p*self(self, state^(1<<(d-1)));
                expect += p*self(self, state^(1<<d));
                expect += p*self(self, state^(1<<(d+1)));
                ret = min(ret, expect);
            }
            else if (num == 2) {
                // (d-1,d,d+1)のどれか2本が立っている
                double p = 1.0/3; // 遷移確率
                double expect = 1;
                if (state>>(d-1)&1) expect += p*self(self, state^(1<<(d-1)));
                if (state>>d&1) expect += p*self(self, state^(1<<d));
                if (state>>(d+1)&1) expect += p*self(self, state^(1<<(d+1)));
                expect *= 3.0/2.0;
                ret = min(ret, expect);
            }
            else if (num == 1) {
                // (d-1,d,d+1)のどれか1本が立っている
                double expect = 3;
                if (state>>(d-1)&1) expect += self(self, state^(1<<(d-1)));
                if (state>>d&1) expect += self(self, state^(1<<d));
                if (state>>(d+1)&1) expect += self(self, state^(1<<(d+1)));
                ret = min(ret, expect);
            }
        }
        return memo[state] = ret;
    };

    printf("%.16f\n", f(f, S));
}


int main() {
    // solve();
    solve2();
    return 0;
}