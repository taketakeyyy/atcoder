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

// AC
// 上、左、左上の3方向
vector<ll> vy = { -1, 0, -1 };
vector<ll> vx = { 0, -1, -1 };
void solve() {
    ll H, W, N; cin >> H >> W >> N;
    vector holes(H, vector<bool>(W, false)); // 穴の座標
    for(ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        holes[a][b] = true;
    }

    // 座標(h,w)はグリッド内に収まっているか？
    auto is_inside = [&](ll h, ll w) -> bool {
        return (h>=0 && h<H && w>=0 && w<W);
    };

    // dp[h][w] := 座標(h,w)が右下隅となる穴のない正方形の個数
    vector<vector<ll>> dp(H, vector<ll>(W, 0));
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (holes[h][w]) {
                // (h,w)が穴の場合、0個
                dp[h][w] = 0;
                continue;
            }

            // dp[h][w] := 上、左、左上の3マスのうち、最も最小の個数+1
            ll mn = INF;
            for(ll vi=0; vi<3; vi++) {
                ll nh = h + vy[vi];
                ll nw = w + vx[vi];
                if (!is_inside(nh, nw)) {
                    // 範囲外のとき
                    mn = 0;
                    break;
                }
                else {
                    // 範囲内のとき
                    mn = min(mn, dp[nh][nw]);
                }
            }
            dp[h][w] = mn + 1;
        }
    }

    // 答え
    ll ans = 0;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            ans += dp[h][w];
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}