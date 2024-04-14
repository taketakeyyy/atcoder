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
    ll N; cin >> N;
    vector<ll> W(N), X(N);
    for(ll i=0; i<N; i++) {
        cin >> W[i] >> X[i];
    }

    ll ans = 0;
    for(ll s=0; s<=23; s++) { // 会議の世界標準時の開始時間
        ll total = 0;
        for(ll i=0; i<N; i++) {
            ll t1 = s + X[i];
            t1 %= 24;
            ll t2 = (t1 + 1)%24;
            if (9<=t1 && t1<=18 && 9<=t2 && t2<=18 ) {
                total += W[i];
            }
        }
        ans = max(ans, total);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}