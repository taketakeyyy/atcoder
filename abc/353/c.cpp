#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
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
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll ans = (N-1)*accumulate(A.begin(), A.end(), 0LL);

    // -10^8の個数を探す
    const ll MOD = 100000000;
    ll cnt = 0;
    sort(A.begin(), A.end());
    for(ll i=0; i<N; i++) {
        ll idx = lower_bound(A.begin()+i+1, A.end(), MOD-A[i]) - A.begin(); // 二分探索する範囲は徐々に減らしていくのがミソ
        cnt += (N-idx);
    }
    ans -= cnt*MOD;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}