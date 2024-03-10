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


// 解説AC
void solve() {
    ll N; cin >> N;
    vector P(N, vector(N,0LL));
    vector R(N, vector(N-1,0LL));
    vector D(N-1, vector(N,0LL));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) cin >> P[i][j];
    }
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N-1; j++) cin >> R[i][j];
    }
    for(ll i=0; i<N-1; i++) {
        for(ll j=0; j<N; j++) cin >> D[i][j];
    }

    // dp処理の内容
    auto f = [&](ll i, ll j, ll p, pair<ll,ll> val, vector<vector<map<ll,pair<ll,ll>>>> &dp, ll d) {
        auto[cost, money] = val;

        // マスにとどまる回数を決める
        if (d > money) {
            d -= money;
            money = 0;
            ll cnt = intceil(d,p); // マスにとどまる回数
            cost += cnt;
            money += p*cnt-d;
        }
        else {
            money -= d;
        }
        cost++; // 移動コスト

        // 更新処理
        ll new_p = max(p, P[i][j]);
        if (dp[i][j].count(new_p)) {
            auto[ncost, nmoney] = dp[i][j][new_p];
            if (cost == ncost) {
                dp[i][j][new_p] = {cost, max(money, nmoney)}; // 所持金が大きい方を採用
            }
            else if (cost < ncost){
                dp[i][j][new_p] = {cost, money}; // 行動回数が小さい方を採用
            }
        }
        else {
            dp[i][j][new_p] = {cost, money};
        }
    };

    // dp[i][j][p] := マス(i,j)まで見て、今まで通過したマスの最大のPがpのときの、(行動回数,所持金)の最適値（行動回数は最小、所持金は最大）
    vector dp(N, vector(N, map<ll,pair<ll,ll>>()));
    dp[0][0][P[0][0]] = {0,0};
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (i==0 and j==0) continue;

            if (i-1 >= 0) {
                for(auto [p, val]: dp[i-1][j]) {
                    f(i, j, p, val, dp, D[i-1][j]);
                }
            }
            if (j-1 >= 0) {
                for(auto [p, val]: dp[i][j-1]) {
                    f(i, j, p, val, dp, R[i][j-1]);
                }
            }
        }
    }

    // 答え
    ll ans = INF;
    for(auto[p, val]: dp[N-1][N-1]) {
        chmin(ans, val.first);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}