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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, M, P; cin >> N >> M >> P;
    vector<ll> A(N), B(M);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<M; i++) cin >> B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    vector<ll> rB(M+1, 0); // Bの累積和
    for(ll i=0; i<M; i++) {
        rB[i+1] = rB[i]+B[i];
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ll a = A[i];
        ll idx = upper_bound(B.begin(), B.end(), P-a) - B.begin();
        ans += rB[idx] + a*idx;
        ans += (M-idx)*P;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}