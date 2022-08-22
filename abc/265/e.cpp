#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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


// 使用する座標は高々C(302, 2) = 45451個
// （3種類のワープの合計が300回なので、 ooooo...oo|| の組み合わせ）
// dp[i][{x,y}] := i回目のワープで、座標{x,y}に到達する場合の数
// ただし以下はdp[i][{x,y}]が重いのかTLEする
void solve1() {
    ll N, M; cin >> N >> M;
    ll A, B, C, D, E, F; cin >> A >> B >> C >> D >> E >> F;
    set<pair<ll,ll>> syogai;
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        syogai.insert({x,y});
    }

    vector<map<pair<ll,ll>,ll>> dp(N+1);  // これ重いんか？TLEする
    dp[0][{0,0}] = 1;
    if (!syogai.count({A,B})) dp[1][{A,B}] = 1;
    if (!syogai.count({C,D})) dp[1][{C,D}] = 1;
    if (!syogai.count({E,F})) dp[1][{E,F}] = 1;
    for(ll i=2; i<=N; i++) {
        for(auto[key, val]: dp[i-1]) {
            auto[x, y] = key;
            if (!syogai.count({x+A, y+B})) {
                dp[i][{x+A, y+B}] += val;
                dp[i][{x+A, y+B}] %= MOD;
            }
            if (!syogai.count({x+C, y+D})) {
                dp[i][{x+C, y+D}] += val;
                dp[i][{x+C, y+D}] %= MOD;
            }
            if (!syogai.count({x+E, y+F})) {
                dp[i][{x+E, y+F}] += val;
                dp[i][{x+E, y+F}] %= MOD;
            }
        }
    }

    // 答え
    ll ans = 0;
    for(auto [_, val]: dp[N]) {
        ans += val; ans %= MOD;
    }
    cout << ans << endl;
}


// 使用する座標は高々C(302, 2) = 45451個
// （3種類のワープの合計が300回なので、 ooooo...oo|| の組み合わせ）
// dp[i][{x,y}] := i回目のワープで、座標{x,y}に到達する場合の数
void solve2() {
    ll N, M; cin >> N >> M;
    ll A, B, C, D, E, F; cin >> A >> B >> C >> D >> E >> F;
    set<pair<ll,ll>> syogai;  // 障害物の座標
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        syogai.insert({x,y});
    }

    // vector<map<pair<ll,ll>,ll>> dp(N+1);  // これ重いのかTLEするので注意
    map<pair<ll,ll>,ll> dp;  // 直前の状態しか必要ない
    if (!syogai.count({A,B})) dp[{A,B}] = 1;
    if (!syogai.count({C,D})) dp[{C,D}] = 1;
    if (!syogai.count({E,F})) dp[{E,F}] = 1;
    for(ll i=2; i<=N; i++) {
        map<pair<ll,ll>,ll> new_dp;
        for(auto[key, val]: dp) {
            auto[x, y] = key;
            if (!syogai.count({x+A, y+B})) {
                new_dp[{x+A, y+B}] += val;
                new_dp[{x+A, y+B}] %= MOD;
            }
            if (!syogai.count({x+C, y+D})) {
                new_dp[{x+C, y+D}] += val;
                new_dp[{x+C, y+D}] %= MOD;
            }
            if (!syogai.count({x+E, y+F})) {
                new_dp[{x+E, y+F}] += val;
                new_dp[{x+E, y+F}] %= MOD;
            }
        }
        dp = new_dp;  // swap(dp, new_dp);
    }

    // 答え
    ll ans = 0;
    for(auto [_, val]: dp) {
        ans += val; ans %= MOD;
    }
    cout << ans << endl;
}


// dp[n][a][b] := n回のワープのうち3種類のワープをそれぞれa,b回行うような移動経路の個数
void solve3() {
    ll N, M; cin >> N >> M;
    ll A, B, C, D, E, F; cin >> A >> B >> C >> D >> E >> F;
    set<pair<ll,ll>> syogai;  // 障害物の座標
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        syogai.insert({x,y});
    }

    vector dp(1, vector<ll>(1));
    dp[0][0] = 1;
    for(ll n=0; n<N; n++) {
        vector new_dp(n+2, vector<ll>(n+2));
        for(ll a=0; a<=n; a++) {
            for(ll b=0; b<=n-a; b++) {
                ll x = a*A + b*C + (n-a-b)*E;
                ll y = a*B + b*D + (n-a-b)*F;

                if (!syogai.count({x+A,y+B})) {
                    new_dp[a+1][b] += dp[a][b];
                    new_dp[a+1][b] %= MOD;
                }
                if (!syogai.count({x+C,y+D})) {
                    new_dp[a][b+1] += dp[a][b];
                    new_dp[a][b+1] %= MOD;
                }
                if (!syogai.count({x+E,y+F})) {
                    new_dp[a][b] += dp[a][b];
                    new_dp[a][b] %= MOD;
                }
            }
        }
        dp = new_dp;
    }

    // 出力
    ll ans = 0;
    for(ll a=0; a<=N; a++) {
        for(ll b=0; b<=N-a; b++) {
            ans += dp[a][b]; ans %= MOD;
        }
    }
    cout << ans << endl;
}

int main() {
    // solve1();
    // solve2();
    solve3();
    return 0;
}