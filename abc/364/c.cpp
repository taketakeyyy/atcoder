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
    ll N, X, Y; cin >> N >> X >> Y;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];

    ll ans = INF;
    auto f = [&](vector<ll> A, ll X) {
        sort(A.begin(), A.end());
        reverse(A.begin(), A.end());
        ll point = 0;
        ll cnt = 0;
        for(ll i=0; i<N; i++) {
            cnt++;
            point += A[i];
            if (point > X) break;
        }
        return cnt;
    };
    ans = f(A, X);
    ans = min(ans, f(B, Y));
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}