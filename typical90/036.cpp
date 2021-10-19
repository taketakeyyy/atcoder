#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    ll N, Q; cin >> N >> Q;
    vector<ll> X(N);
    vector<ll> Y(N);
    for(int i=0; i<N; i++) {
        cin >> X[i] >> Y[i];
    }

    // マンハッタン距離は45度回転
    // すると各点の距離はチェビシェフ距離となる（なんで？）
    // ある点から最も遠い点の探索は、X座標の最小値、X座標の最大値、Y座標の最小値、Y座標の最大値と比較して、最も遠いチェビシェフ距離の点が答えとなる
    ll minX = INF, maxX = -INF;
    ll minY = INF, maxY = -INF;
    for(ll i=0; i<N; i++) {
        ll x = X[i] - Y[i];
        ll y = X[i] + Y[i];
        X[i] = x;
        Y[i] = y;
        minX = min(minX, x); maxX = max(maxX, x);
        minY = min(minY, y); maxY = max(maxY, y);
    }

    // クエリ処理
    for(ll i=0; i<Q; i++) {
        ll q; cin >> q; q--;
        ll ans = -INF;
        ans = max(ans, abs(minX - X[q]));
        ans = max(ans, abs(maxX - X[q]));
        ans = max(ans, abs(minY - Y[q]));
        ans = max(ans, abs(maxY - Y[q]));
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}