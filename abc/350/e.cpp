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


void solve() {
    ll N, A, X, Y;
    cin >> N >> A >> X >> Y;

    map<ll,double> memo; // E[n]のメモ値
    memo[0] = 0.0;
    auto E = [&](auto E, ll n) {
        // 終了条件
        if (memo.contains(n)) return memo[n];

        double mn = (double)INF;
        { // Xの操作
            double res = X+E(E,n/A);
            mn = min(mn, res);
        }
        {// Yの操作
            double res = Y;
            double p = 1.0/6.0;
            for(ll i=2; i<=6; i++) {
                res += E(E,n/i) * p;
            }
            res *= (double)6.0/5.0;
            mn = min(mn, res);
        }
        return memo[n] = mn;
    };
    double ans = E(E, N);
    printf("%.10lf\n", ans);
}


int main() {
    solve();
    return 0;
}