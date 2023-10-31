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

// yunipoke-san
// O(MQ2^N)
void solve() {
    ll N, M, P, Q, R; cin >> N >> M >> P >> Q >> R;
    vector<ll> X(R), Y(R), Z(R);
    vector<vector<pair<ll,ll>>> G(N); // G[i] := 女子iが渡したいチョコ(男子, 幸福度)のリスト
    for(ll i=0; i<R; i++) {
        cin >> X[i] >> Y[i] >> Z[i];
        X[i]--; Y[i]--;
        G[X[i]].push_back(make_pair(Y[i], Z[i]));
    }

    ll ans = 0;
    for(ll bit=0; bit<(1<<N); bit++) { // 女子の選び方を全探索
        if (__builtin_popcount(bit) != P) continue; // bitの立っているビットがP個じゃないときはスキップ

        ll A[M] = {}; // A[y] := 男子yにチョコを上げたときの幸福度
        for(ll d=0; d<N; d++) {
            if (bit>>d&1) {
                for(const auto &[y,z]: G[d]) {
                    A[y] += z;
                }
            }
        }

        // 今、女子は固定した。どの男子を旅行グループに選べば幸福度は最大になるか？
        // dp[i][k] := i番目の男子まで見て、k人選んだときの、幸福度の最大値
        vector<ll> dp(Q+1, -INF);
        dp[0] = 0;
        for(ll i=0; i<M; i++) {
            auto newdp = dp;
            for(ll k=0; k<Q; k++) {
                chmax(newdp[k+1], dp[k]+A[i]);
            }
            dp = newdp;
        }
        ans = max(ans, dp[Q]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}