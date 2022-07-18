#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
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


void solve() {
    // bitDPの解法
    ll N, K; cin >> N >> K;
    vector<ll> X(N), Y(N);
    for(ll i=0; i<N; i++) { cin >> X[i] >> Y[i]; }

    vector dist(N, vector<ll>(N, 0));  // dist[i][j] := 点iと点j間の距離(の2乗)
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            dist[i][j] = (X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]);
        }
    }

    vector<ll> cost(1<<N, 0);  // cost[bit] := 点集合がbitのときのコスト(2点間距離の最大値)
    for(ll bit=1; bit<1<<N; bit++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<i; j++) {
                if ((bit>>i&1) && (bit>>j&1)) {
                    cost[bit] = max(cost[bit], dist[i][j]);
                }
            }
        }
    }

    vector dp(1<<N, vector<ll>(K+1, INF));  // dp[bit][k] := 既に選んだ点がbitのときで、現在のグループ数がkのときのコストの最小値
    dp[0][0] = 0;
    for(ll k=1; k<=K; k++) {
        for(ll bit=1; bit<1<<N; bit++) {  // 選んだ点集合をbitで表す(部分集合)
            for(ll bit2=bit; bit2!=0; bit2=(bit2-1)&bit) {  // bit2 := bitで表されるものから何個か選んだもの(部分集合の部分集合)
                dp[bit][k] = min(dp[bit][k], max(dp[bit^bit2][k-1], cost[bit2]));
            }
        }
    }
    cout << dp[(1<<N)-1][K] << endl;
}


int main() {
    solve();
    return 0;
}