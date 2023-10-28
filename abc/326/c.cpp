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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());

    { // 0始まりにする
        ll a = A[0];
        for(ll i=0; i<N; i++) A[i] -= a;
    }

    // 二分探索
    ll ans = -1;
    for(ll i=0; i<N; i++) {
        ll l = i;
        ll r = lower_bound(A.begin(), A.end(), A[l]+M) - A.begin();
        r--;
        ans = max(ans, r-l+1);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}