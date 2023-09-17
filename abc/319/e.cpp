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


// 解説AC
void solve() {
    ll N, X, Y; cin >> N >> X >> Y;
    vector<pair<ll,ll>> stops;
    for(ll i=0; i<N-1; i++) {
        ll p, t; cin >> p >> t;
        stops.push_back({p,t});
    }

    // 高橋が青木の家までにかかる時間は、lcm(1,2,...,8)=840で周期する
    ll LCM = 1;
    for(ll i=1; i<=8; i++) LCM = lcm(LCM,i);
    // dp[t] := LCMで割ったあまりがtの時刻に高橋が出発したときに、青木の家に到着するまでにかかる時間
    vector<ll> dp(LCM);
    for(ll t=0; t<LCM; t++) {
        ll now_t = t + X; // 現在時刻
        for(ll i=0; i<N-1; i++) {
            auto[p, bus_t] = stops[i];
            if (now_t%p == 0) now_t += bus_t;
            else now_t += (p-now_t%p) + bus_t;
        }
        now_t += Y;
        dp[t] = now_t - t;
    }

    // クエリ処理
    ll Q; cin >> Q;
    vector<ll> ans(Q);
    for(ll q=0; q<Q; q++) {
        ll t; cin >> t;
        ans[q] = dp[t%LCM] + t;
    }

    // 答え
    for(ll q=0; q<Q; q++) cout << ans[q] << endl;
}


int main() {
    solve();
    return 0;
}