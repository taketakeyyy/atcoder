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
    vector<ll> A(N), B(M);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<M; i++) cin >> B[i];

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ll ans = 0;
    ll m = 0;
    for(ll i=0; i<N; i++) {
        if (m == M) break;
        if (B[m] <= A[i]) {
            ans += A[i];
            m++;
        }
    }

    if (m == M) {
        cout << ans << endl;
    }
    else {
        cout << -1 << endl;
    }

}


int main() {
    solve();
    return 0;
}