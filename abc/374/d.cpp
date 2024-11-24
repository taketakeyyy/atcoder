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
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(double& x, double y) { x = max(x,y); }
void chmin(double& x, double y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


void solve() {
    ll N, S, T; cin >> N >> S >> T;
    vector<ll> A(N), B(N), C(N), D(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }

    // (a,b) -> (c,d)へ速度vで移動するときの時間
    auto f = [&](ll a, ll b, ll c, ll d, ll v) -> double {
        double dist = sqrt((c-a)*(c-a) + (d-b)*(d-b));
        return dist / (double)v;
    };

    // 順序Pを全探索
    vector<ll> P(N);
    for(ll i=0; i<N; i++) P[i] = i;
    sort(P.begin(), P.end());
    double ans = INF;
    do {
        // dp[j] := j=0:(a,b)側にいるときの最小時間, j=1:(c,d)側にいるときの最小時間
        vector<double> dp(2, 0);
        ll preA=0, preB=0, preC=0, preD=0;
        for(ll i=0; i<N; i++) {
            vector<double> newdp(2, INF);
            ll p = P[i];
            ll a = A[p];
            ll b = B[p];
            ll c = C[p];
            ll d = D[p];
            // (preA,preB) -> (C,D) -> (A,B)の場合
            chmin(newdp[0], dp[0]+f(preA,preB,c,d,S)+f(c,d,a,b,T));
            // (preC,preD) -> (C,D) -> (A,B)の場合
            chmin(newdp[0], dp[1]+f(preC,preD,c,d,S)+f(c,d,a,b,T));
            // (preA,preB) -> (A,B) -> (C,D)の場合
            chmin(newdp[1], dp[0]+f(preA,preB,a,b,S)+f(a,b,c,d,T));
            // (preC,preD) -> (A,B) -> (C,D)の場合
            chmin(newdp[1], dp[1]+f(preC,preD,a,b,S)+f(a,b,c,d,T));
            swap(newdp,dp);
            preA = a;
            preB = b;
            preC = c;
            preD = d;
        }
        chmin(ans, dp[0]);
        chmin(ans, dp[1]);
    }while (next_permutation(P.begin(), P.end()));
    printf("%.10lf\n", ans);
}


int main() {
    solve();
    return 0;
}