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


// ここでの部分文字列の定義に注意
// 先頭と末尾から0文字以上取り去って得られるACGT文字列の最長の長さは、
// 連続するACGT文字列の最長の長さを求めれば良い。
void solve() {
    string S; cin >> S;

    ll ans = 0;
    ll seq = 0;
    for(auto c: S) {
        if (c=='A' || c=='C' || c=='G' || c=='T') {
            seq++;
        }
        else {
            ans = max(ans, seq);
            seq = 0;
        }
    }
    ans = max(ans, seq);

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}