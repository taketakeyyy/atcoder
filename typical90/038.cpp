#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve() {
    ll A, B; cin >> A >> B;
    const ll LARGE = 1000000000000000000;

    // LCM(a, b) = a * b / gcd(a,b)
    // ここで、
    // LARGE >= a * b / gcd(a, b)
    // でなければならない。両辺aで割ると、
    // LARGE / a >= b / gcd(a, b)
    // この条件を満たさない場合、LARGEと出力する
    ll r = B / gcd(A,B);
    if (LARGE/A < r) {
        cout << "Large" << endl;
        return;
    }

    // 出力
    cout << A * r << endl;
    return;
}


int main() {
    solve();
    return 0;
}