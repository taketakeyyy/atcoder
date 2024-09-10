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
    ll N; cin >> N;
    ll A = 0; // 1個の寿司が乗っている皿の枚数
    ll B = 0; // 2個の寿司が乗っている皿の枚数
    ll C = 0; // 3個の寿司が乗っている皿の枚数
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (a == 1) A++;
        if (a == 2) B++;
        if (a == 3) C++;
    }

    // dp[a][b][c] := 現在、1個の寿司が乗っている皿がa枚、2個の寿司が乗っている皿がb枚、3個の寿司が乗っている皿がc枚の状態で、終了するまでに行われる操作回数の期待値
    // 遷移が(a+1, b-1, c), (a, b+1, c-1)とあるので、dp[A+1][B+1][C]まで求める必要があるので、dpのaとbのサイズはかなり大きめに確保しておく必要がある(+1だと全然足りない)
    // 遷移が複雑なので、ループではなくメモ化再帰で解いた方が簡単
    vector dp(303, vector<vector<double>>(303, vector<double>(C+1, 0.0)));
    dp[0][0][0] = 0.0;

    vector memo(303, vector<vector<bool>>(303, vector<bool>(C+1, false)));
    memo[0][0][0] = true;
    auto f = [&](auto self, ll a, ll b, ll c) -> double {
        if (memo[a][b][c]) return dp[a][b][c];
        memo[a][b][c] = true;

        // dpの更新
        double p1 = 1.0 - (double)(a+b+c)/N;
        double p2 = (double)c/N;
        double p3 = (double)b/N;
        double p4 = (double)a/N;
        dp[a][b][c] = 1;
        if (a-1 >= 0) dp[a][b][c] += p4*self(self, a-1, b, c);
        if (b-1 >= 0) dp[a][b][c] += p3*self(self, a+1, b-1, c);
        if (c-1 >= 0) dp[a][b][c] += p2*self(self, a, b+1, c-1);
        dp[a][b][c] /= (1.0-p1);
        return dp[a][b][c];
    };

    printf("%.10f\n", f(f,A,B,C));
}


int main() {
    solve();
    return 0;
}