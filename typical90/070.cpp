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
    // x, y独立に考える
    ll N; cin >> N;
    vector<ll> Xs(N);
    vector<ll> Ys(N);
    for (ll i=0; i<N; i++) {
        cin >> Xs[i] >> Ys[i];
    }

    // 発電所を建てるのは中央値が最適値
    sort(Xs.begin(), Xs.end());
    sort(Ys.begin(), Ys.end());
    ll xx = Xs[N/2];
    ll yy = Ys[N/2];

    // 答えを計算
    ll ans = 0;
    for (ll i=0; i<N; i++) {
        ans += abs(Xs[i]-xx) + abs(Ys[i]-yy);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}