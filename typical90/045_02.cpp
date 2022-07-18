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


// 自分なりにわかりやすくしたつもり
void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> X(N), Y(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i];
    }

    // dist[i][j] := 頂点iとjの距離
    vector<vector<ll>> dist(N, vector<ll>(N, INF));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            dist[i][j] = (X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]);
        }
    }

    // score[bit] := グループ内の点集合がbitのときのスコア
    vector<ll> score(1<<N, 0);
    for(ll bit=0; bit<(1<<N); bit++) {
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                if ((bit>>i&1) && (bit>>j&1)) {
                    score[bit] = max(score[bit], dist[i][j]);
                }
            }
        }
    }

    // dp[bit][k] := 使われた点集合がbitのときの、現在のグループ数がk個のときの、スコアの最小値
    vector dp(1<<N, vector<ll>(K+1, INF));
    for(ll bit=1; bit<(1<<N); bit++) { dp[bit][1] = score[bit]; }
    for(ll k=2; k<=K; k++) {
        for(ll bit=1; bit<(1<<N); bit++) {  // 使われた点集合(全体の部分集合)
            for(ll bit2=bit; bit2!=0; bit2=((bit2-1)&bit)) {  // bit2 := 新しく追加されるグループの点集合(bitの部分集合)
                dp[bit][k] = min(dp[bit][k], max(dp[bit^bit2][k-1], score[bit2]));
            }
        }
    }

    // 出力
    cout << dp[(1<<N)-1][K] << endl;
}


int main() {
    solve();
    return 0;
}