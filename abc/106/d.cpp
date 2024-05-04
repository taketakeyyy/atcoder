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


/**
 * @brief ２次元配列Aから、二次元累積和を作る O(HW)
 *
 * @param A
 * @return vector<vector<ll>> ２次元累積和
 * @note 0列目と0行目は必ず0なので注意
 */
vector<vector<ll>> make_ruiseki2d(const vector<vector<ll>> &A) {
    auto rui = A;
    ll H = A.size();
    ll W = A[0].size();

    // 横方向に累積和
    for(ll i=0; i<H; i++) {
        for(ll j=1; j<W; j++) rui[i][j] += rui[i][j-1];
    }
    // 縦方向に累積和
    for(ll j=0; j<W; j++) {
        for(ll i=1; i<H; i++) rui[i][j] += rui[i-1][j];
    }
    return rui;
}

// 解説AC ２次元累積和 O(N^2)
void solve() {
    ll N, M, Q; cin >> N >> M >> Q;
    vector<ll> L(M), R(M);
    for(ll i=0; i<M; i++) {
        cin >> L[i] >> R[i];
    }

    // ２次元累積和を作る
    vector<vector<ll>> A(N+1, vector<ll>(N+1, 0LL));
    for(ll i=0; i<M; i++) {
        A[R[i]][L[i]] += 1;
    }
    auto rui = make_ruiseki2d(A);

    // クエリ処理
    for(ll _=0; _<Q; _++) {
        ll p, q; cin >> p >> q;
        ll ans = rui[q][q] - rui[p-1][q] - rui[q][p-1] + rui[p-1][p-1];
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}