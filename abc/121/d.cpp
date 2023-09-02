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


// 累積xor
void solve() {
    ll A, B; cin >> A >> B;

    // f(a) := 0 xor 1 xor ... xor a を計算する
    auto f = [&](ll a) -> ll {
        ll sum_one = (a/2)%2;
        if (a%2 == 0) {
            return sum_one ^ a;
        }
        else {
            return sum_one ^ (a-1) ^ a;
        }
    };

    // 答え
    if (A == 0) {
        cout << f(B) << endl;
    }
    else {
        // F(A,B) = f(A-1) xor f(B)
        ll ans = f(A-1)^f(B);
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}