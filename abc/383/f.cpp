#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }

// 色でソートしておくと、前から見て行って買うか買わないか決めていく際に、直前に買ったものと色が違うなら色の種類数が+1されるとかになるんで、
// すでに購入した色の情報の管理が1ビットで済むようになる。なので、(位置)×(残り金額)×(今の色が直前に買った色と同じか)でDPすればいい
// らしい
void solve() {
    ll N, X, K; cin >> N >> X >> K;
    vector<tuple<ll,ll,ll>> items; // (色,価格,効用)
    for(ll i=0; i<N; i++) {
        ll p, u, c; cin >> p >> u >> c;
        items.emplace_back(c,p,u);
    }
    sort(items.begin(), items.end());

    // dp[i][x][j] := i番目まで見て、合計価格がx円以下で、今見てる色をすでに買ったか(j)どうかのときの、満足度のmax
    vector dp(50000+1, vector(2, 0LL));
    ll pre_c = -1; // 前回の色
    for(ll i=0; i<N; i++) {
        auto[c,p,u] = items[i];

        if (pre_c != c) {
            // 色が変わったならば、jをリセットする
            for(ll x=0; x<=X; x++) {
                chmax(dp[x][0], dp[x][1]);
            }
            pre_c = c;
        }

        vector newdp(50000+1, vector(2, 0LL));
        for(ll x=0; x<=X; x++) {
            // 今回の商品を買わない場合
            for(ll j=0; j<2; j++) {
                chmax(newdp[x][j], dp[x][j]);
            }

            // 今回の商品を買う場合
            ll nx = x + p;
            if (nx <= X) {
                chmax(newdp[nx][1], dp[x][1]+u);
                chmax(newdp[nx][1], dp[x][0]+u+K);
            }
        }

        swap(newdp, dp);
    }

    // 答え
    ll ans = -1;
    for(ll x=0; x<=X; x++) {
        for(ll j=0; j<2; j++) chmax(ans, dp[x][j]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}