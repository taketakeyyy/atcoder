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
    string S; cin >> S;
    string T; cin >> T;
    ll diff;
    if (S[0] <= T[0]) {
        diff = T[0]-S[0];
    }
    else {
        diff = T[0]-S[0]+26;
    }

    for(ll i=0; i<S.size(); i++) {
        if ((S[i]+diff)%26 == T[i]%26) continue;
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