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
    ll A, B; cin >> A >> B;

    // 一気に引く
    ll ans = 0;
    while(A != B) {
        if (A > B) {
            ll cnt = A/B;
            if (A-cnt*B == 0) { // 引きすぎ注意
                A -= (cnt-1)*B;
                ans += cnt-1;
            }
            else {
                A -= cnt*B;
                ans += cnt;
            }
        }
        else {
            ll cnt = B/A;
            if (B-cnt*A == 0) {
                B -= (cnt-1)*A;
                ans += cnt-1;
            }
            else {
                B -= cnt*A;
                ans += cnt;
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}