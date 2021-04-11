#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    string S; cin >> S;
    ll l=0, r=S.size()-1;

    while(r-l > 0) {
        if (S[l]=='0') {
            l++; continue;
        }
        if (S[r]=='0') {
            r--; continue;
        }
        break;
    }

    if (r-l <= 0) {
        cout << "Yes" << endl;
        return;
    }

    while((r-l)>0) {
        if (S[l]==S[r]) {
            l++; r--;
            continue;
        }
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    return;
}


int main() {
    solve();
    return 0;
}