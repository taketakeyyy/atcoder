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
    vector<ll> S(8);
    for(ll i=0; i<8; i++) cin >> S[i];

    bool is_ok = true;
    for(ll i=1; i<8; i++) {
        if (S[i-1] <= S[i]) continue;
        is_ok = false;
        break;
    }
    if (!is_ok) {
        cout << "No" << endl;
        return;
    }

    for(ll i=0; i<8; i++) {
        if (!(S[i]>=100 && S[i]<=675)) {
            cout << "No" << endl;
            return;
        }
    }

    is_ok = true;
    for(ll i=0; i<8; i++) {
        if (S[i]%25 == 0) continue;
        is_ok = false;
        break;
    }
    if (!is_ok) {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}