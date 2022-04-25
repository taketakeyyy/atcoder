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


void solve() {
    vector<char> S(3);
    for(ll i=0; i<3; i++) cin >> S[i];
    vector<char> T(3);
    for(ll i=0; i<3; i++) cin >> T[i];

    ll diff = 0;
    if (S[0]!=T[0]) diff++;
    if (S[1]!=T[1]) diff++;
    if (S[2]!=T[2]) diff++;

    if (diff == 0) {
        // 最初から揃っている
        cout << "Yes" << endl;
    }
    else if (diff == 1) {
        // 存在しない
        ;
    }
    else if (diff == 2) {
        // 1回の操作で揃えられる。
        cout << "No" << endl;
    }
    else {
        // 2回の走査で揃えられる
        cout << "Yes" << endl;
    }
}


int main() {
    solve();
    return 0;
}