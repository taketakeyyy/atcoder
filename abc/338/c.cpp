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
    vector<ll> Q(N);
    for(ll i=0; i<N; i++) cin >> Q[i];
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];

    // 料理Aは最大で何個作れるか？
    ll mxA = INF;
    for(ll i=0; i<N; i++) {
        if (A[i]==0) continue;
        ll cnt = Q[i]/A[i];
        chmin(mxA, cnt);
    }

    // 料理Aをn個作る方法を全探索する
    ll ans = 0;
    for(ll n=0; n<=mxA; n++) {
        ll mxB = INF;
        for(ll i=0; i<N; i++) {
            if (B[i]==0) continue;
            ll rest = Q[i]-A[i]*n;
            ll cnt = rest/B[i];
            chmin(mxB, cnt);
        }
        chmax(ans, n+mxB);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}