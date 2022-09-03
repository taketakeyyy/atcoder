#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
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
    ll N, M; cin >> N >> M;
    vector<ll> A(N+1);
    vector<ll> rA(N+1);  // 累積和
    for(ll i=1; i<N+1; i++) {
        cin >> A[i];
        rA[i] += rA[i-1] + A[i];
    }

    ll ans = -INF;
    ll total = 0;
    for(ll i=1; i<M+1; i++) {
        total += i*A[i];
    }
    ans = max(ans, total);

    // 尺取法
    for(ll i=M+1; i<=N; i++) {
        ll diff = rA[i-1] - rA[i-1-M];
        total -= diff;
        total += M*A[i];
        ans = max(ans, total);
    }
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}