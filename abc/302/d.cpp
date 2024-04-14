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
    ll N, M, D; cin >> N >> M >> D;
    vector<ll> A(N), B(M);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<M; i++) cin >> B[i];

    ll ans = -1;
    sort(B.begin(), B.end());
    for(ll i=0; i<N; i++) {
        auto idx = lower_bound(B.begin(), B.end(), A[i]+D) - B.begin();
        if (idx == M) {
            idx--;
            if (B[idx] >= A[i]-D && B[idx] <= A[i]+D) {
                ans = max(ans, B[idx]+A[i]);
            }
        }
        else if (B[idx] == A[i]+D) {
            ans = max(ans, B[idx]+A[i]);
        }
        else {
            idx--;
            if (idx == -1) continue;
            if (B[idx] >= A[i]-D && B[idx] <= A[i]+D) {
                ans = max(ans, B[idx]+A[i]);
            }
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}