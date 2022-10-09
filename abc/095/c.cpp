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
    ll A, B, C, X, Y; cin >> A >> B >> C >> X >> Y;

    ll ans = 0;
    if (A+B >= 2*C) {
        // ABピザ2枚買ってA,Bを1枚作ったほうがお得
        ll mn = min(X, Y);
        ans += 2*C*mn;

        if (Y == mn) {
            // Aピザを買い足す
            ll rest = X - mn;
            if (A >= 2*C) {
                // ABピザ2枚買ったほうがお得
                ans += 2*C*rest;
            }
            else {
                ans += A*rest;
            }
        }
        else {
            // Bピザを買い足す
            ll rest = Y - mn;
            if (B >= 2*C) {
                ans += 2*C*rest;
            }
            else {
                ans += B*rest;
            }
        }
    }
    else {
        // AピザとBピザをそれぞれ買ったほうがお得
        ans += A*X + B*Y;
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}