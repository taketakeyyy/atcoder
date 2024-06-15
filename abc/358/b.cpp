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
    ll N, A; cin >> N >> A;
    vector<ll> T(N);
    for(ll i=0; i<N; i++) cin >> T[i];

    vector<ll> ans(N);
    ans[0] = T[0]+A;
    ll now = T[0]+A;
    for(ll i=1; i<N; i++) {
        if (T[i] < now) {
            ans[i] = now+A;
            now = ans[i];
        }
        else {
            ans[i] = T[i]+A;
            now = ans[i];
        }
    }

    // 出力
    for(ll i=0; i<N; i++) cout << ans[i] << endl;
}


int main() {
    solve();
    return 0;
}