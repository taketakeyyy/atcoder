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


// 人pが勝つ確率
double win_rate (double rp, double rq){
    return 1.0/(1.0+pow(10,(rq-rp)/400.0));
}

void solve() {
    ll K; cin >> K;
    ll N = 1; // 人の人数
    for(ll k=0; k<K; k++) N *= 2;
    vector<ll> R(N);
    for(ll i=0; i<N; i++) cin >> R[i];

    // dp[i][j] := 人iがj回戦目に勝つ確率(すべて0-indexed)
    vector dp(N, vector<double>(K, 0));
    // 0回戦目
    for(ll i=0; i<N; i++) {
        ll other = i^1LL; // 0回戦目の対戦相手
        dp[i][0] = win_rate(R[i], R[other]);
    }
    // 1回戦目以降
    for(ll j=1; j<K; j++) {
        for(ll i=0; i<N; i++) {
            ll other_base = i;
            other_base ^= (1<<j); // j桁目反転
            other_base &= ~((1<<j)-1); // j-1桁目以下を0にする
            for(ll k=0; k<(1<<j); k++) {
                ll other = other_base + k; // j回戦目で戦う人
                dp[i][j] += dp[i][j-1] * dp[other][j-1] * win_rate(R[i], R[other]);
            }
        }
    }

    // 答え
    for(ll i=0; i<N; i++) {
        printf("%.10f\n", dp[i][K-1]);
    }
}


int main() {
    solve();
    return 0;
}