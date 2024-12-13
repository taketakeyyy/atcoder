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

/**
 * @brief 配列Aの値を座標圧縮する O(N)
 *
 * @param A
 * @return pair<map<ll,ll>, map<ll,ll>>
 * 以下の2つのmapを返す
 *  a2c[a] := もとの値aをキーにして、座標圧縮後の値cを返すmap
 *  c2a[c] := 座標圧縮後の値cをキーにして、もとの値aを返すmap
 *
 * @example
 *  // Aの値を座標圧縮する A = {1,10,1000,999999,...}
 *  auto[a2c, c2a] = coordinate_compression(A);
 */
pair<map<ll,ll>, map<ll,ll>> coordinate_compression(vector<ll> A) {
    map<ll,ll> a2c, c2a;
    ll N = A.size();
    sort(A.begin(), A.end());

    ll c = 0; // 座標圧縮した値
    ll pre_a = -INF;
    for(ll i=0; i<N; i++) {
        ll a = A[i];
        if (pre_a != a) {
            a2c[a] = c;
            c++;
            pre_a = a;
        }
    }
    return {a2c, c2a};
}

void solve() {
    ll N, W, C; cin >> N >> W >> C;
    vector<ll> Weight(N), Value(N), Color(N);
    for(ll i=0; i<N; i++) {
        ll w, v, c; cin >> w >> v >> c;
        Weight[i] = w;
        Value[i] = v;
        Color[i] = c;
    }
    auto[a2c, c2a] = coordinate_compression(Color);

    // 色を座標圧縮してitemsを作る
    vector<tuple<ll,ll,ll>> items(N); // (色,重さ,価値)
    for(ll i=0; i<N; i++) {
        items[i] = {a2c[Color[i]], Weight[i], Value[i]};
    }
    sort(items.begin(), items.end());

    // dp[i][w][c][j] := i番目のものまで見て、重さはw以下で、色はc種類以下で、今見ている色を使ったかどうか(j)のときの、価値のmax
    vector dp(W+1, vector(C+1, vector(2, -1LL)));
    dp[0][0][0] = 0;
    ll pre_c = -1;
    for(ll i=0; i<N; i++) {
        auto[now_c, now_w, now_v] = items[i];

        // if (pre_c != now_c) {
        //     for(ll w=0; w<W; w++) {
        //         for(ll c=0; c<=C; c++) chmax(dp[w][c][0], dp[w][c][1]);
        //     }
        // }

        vector newdp(W+1, vector(C+1, vector(2, -1LL)));
        // 今回の品物を入れない場合
        for(ll w=0; w<=W; w++) {
            for(ll c=0; c<=C; c++) {
                for(ll j=0; j<2; j++) chmax(newdp[w][c][j], dp[w][c][j]);
            }
        }

        // 今回の品物を入れる場合
        for(ll w=0; w+now_w<=W; w++) {
            for(ll c=0; c<=C; c++) {
                if (dp[w][c][0] != -1) {
                    if (c+1<=C) chmax(newdp[w+now_w][c+1][1], dp[w][c][0]+now_v);
                }
                if (dp[w][c][1] != -1) {
                    if (pre_c==now_c) chmax(newdp[w+now_w][c][1], dp[w][c][1]+now_v); // ここがちがう
                    if (pre_c!=now_c) {
                        if (c+1<=C)chmax(newdp[w+now_w][c+1][1], dp[w][c][1]+now_v);
                    }
                }
            }
        }

        pre_c = now_c;
        swap(newdp, dp);
    }

    // 答え
    ll ans = -1;
    for(ll w=0; w<=W; w++) {
        for(ll c=0; c<=C; c++) {
            for(ll j=0; j<2; j++) chmax(ans, dp[w][c][j]);
        }
    }
    cout << ans << endl;
}


void solve2() {
    ll N, W, C; cin >> N >> W >> C;
    vector<ll> Weight(N), Value(N), Color(N);
    for(ll i=0; i<N; i++) {
        ll w, v, c; cin >> w >> v >> c;
        Weight[i] = w;
        Value[i] = v;
        Color[i] = c;
    }

    // itemsを作る
    vector<tuple<ll,ll,ll>> items(N); // (色,重さ,価値)
    for(ll i=0; i<N; i++) {
        items[i] = {Color[i], Weight[i], Value[i]};
    }
    items.push_back({-1,0,-1}); // ダミー
    sort(items.begin(), items.end());

    // dp[i][j][c][w] := i番目まで見て、最後に使った色がiと同じか(j)で、色の種類数がc以下で、重さがw以下のときの、最大価値
    vector dp(2, vector(C+1, vector(W+1, 0LL)));
    for(ll i=1; i<=N; i++) {
        auto[now_c, now_w, now_v] = items[i];
        auto[pre_c, _, __] = items[i-1];

        vector newdp(2, vector(C+1, vector(W+1, 0LL)));
        for(ll c=1; c<=C; c++) {
            for(ll w=0; w<=W; w++) {
                if (pre_c == now_c) {
                    newdp[1][c][w] = dp[1][c][w];
                    if (w-now_w >= 0) {
                        newdp[1][c][w] = max({
                            newdp[1][c][w],
                            dp[1][c][w-now_w] + now_v,
                            dp[0][c-1][w-now_w] + now_v,
                        });
                    }
                    newdp[0][c][w] = dp[0][c][w];
                }
                else {
                    if (w-now_w >= 0) {
                        newdp[1][c][w] = max(dp[1][c-1][w-now_w]+now_v, dp[0][c-1][w-now_w]+now_v);
                    }
                    newdp[0][c][w] = max(dp[1][c][w], dp[0][c][w]);
                }
            }
        }
        swap(newdp, dp);
    }

    // 答え
    ll ans = max(dp[1][C][W], dp[0][C][W]);
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}