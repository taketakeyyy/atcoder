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
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // どこかで負の値にならないか？
    auto f = [&](ll x) {
        for(ll i=0; i<N; i++) {
            x += A[i];
            if (x < 0) return false; // 負の値になった
        }
        return true; // 負の値にならない
    };

    ll l=0, r=2e14+10;
    while(r-l > 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    ll first;
    if (f(l)) first=l;
    else first=r;

    // 現在の乗客は？
    ll ans = accumulate(A.begin(), A.end(), first);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}