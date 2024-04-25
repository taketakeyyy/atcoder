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
    ll N, M; cin >> N >> M;
    vector<ll> A(M), B(M);
    vector<vector<ll>> C(M);
    for(ll i=0; i<M; i++) {
        cin >> A[i] >> B[i];
        for(ll b=0; b<B[i]; b++) {
            ll c; cin >> c; c--;
            C[i].push_back(c);
        }
    }

    // dp[i][s] := i番目の鍵まで見て、開けられる宝箱の状態がsのときの、金額の最小値
    vector<ll> dp(1LL<<N, INF);
    dp[0] = 0LL;
    for(ll m=0; m<M; m++) {
        ll box = 0LL; // 今回開けられる宝箱の状態
        for(ll c: C[m]) {
            box |= 1LL<<c;
        }

        for(ll state=(1LL<<N)-1LL; state>=0; state--) {
            if (dp[state] == INF) continue;
            chmin(dp[state|box], dp[state]+A[m]);
        }
    }

    // 答え
    ll ans = dp[(1LL<<N)-1LL];
    cout << (ans==INF ? -1 : ans) << endl;
}


int main() {
    solve();
    return 0;
}