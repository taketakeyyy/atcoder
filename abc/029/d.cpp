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


// Nの各桁の1が何回書かれるかを数える
void solve() {
    ll N; cin >> N;
    ll ans = 0;
    ll x10 = 1;
    while(1) {
        if (x10 > N) break;

        ll cnt = N/(x10*10);
        ll dnum = (N%(x10*10)/x10);  // d桁目の数字（10の位は2桁目）
        if (dnum == 1) {
            // 312 のとき、 2桁目の1は、0**~2**の3回×10回足されて、
            // 3**台のときだけ、10~12の3回だけ足される
            ans += cnt*x10;
            ans += (N%x10)+1;
        }
        else if (dnum > 1) {
            // 345 のとき、2桁目の1は0**~3**の4回×10回足される
            cnt++;
            ans += cnt*x10;
        }
        else {
            // 305 のとき、2桁目の1は0**~2**の3回×10回足される
            ans += cnt*x10;
        }
        x10 *= 10;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}