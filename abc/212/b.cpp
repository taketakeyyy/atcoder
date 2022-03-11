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
    string X; cin >> X;
    if (X[0]==X[1] && X[1]==X[2] && X[2]==X[3]) {
        cout << "Weak" << endl;
        return;
    }

    bool is_weak = true;
    for(ll i=0; i<3; i++) {
        if (X[i]=='9' && X[i+1]=='0') {
            continue;
        }
        if (X[i]+1 == X[i+1]) {
            continue;
        }
        is_weak = false;
    }

    if (is_weak) {
        cout << "Weak" << endl;
        return;
    }

    cout << "Strong" << endl;
}


int main() {
    solve();
    return 0;
}