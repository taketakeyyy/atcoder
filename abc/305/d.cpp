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
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> ru(N); // 睡眠時間の累積和
    for(ll i=1; i<N; i++) {
        if (i%2 == 0) {
            ru[i] = ru[i-1] + (A[i]-A[i-1]);
        }
        else {
            ru[i] = ru[i-1];
        }
    }

    ll Q; cin >> Q;
    for(ll q=0; q<Q; q++) {
        ll l, r; cin >> l >> r;
        ll ans = 0;

        ll lidx = upper_bound(A.begin(), A.end(), l) - A.begin();
        if (lidx == N) {
            cout << 0 << endl;
            continue;
        }
        if (lidx%2 == 0) {
            ans += A[lidx]-l;
        }

        ll ridx = lower_bound(A.begin(), A.end(), r) - A.begin();
        ridx--;
        if (ridx == -1) {
            cout << 0 << endl;
            continue;
        }
        if (ridx%2 != 0) {
            ans += r-A[ridx];
        }

        ans += ru[ridx] - ru[lidx];
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}