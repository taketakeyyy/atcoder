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
    string s; cin >> s;
    ll ind = find(s.begin(), s.end(), '.') - s.begin();
    string x = s.substr(0, ind);
    string c = s.substr(ind+1, 1);

    int y = c[0] - '0';

    if (0<=y && y<=2) {
        cout << x << "-" << endl;
    }
    else if (3<=y && y<=6) {
        cout << x << endl;
    }
    else {
        cout << x << "+" << endl;
    }
}


int main() {
    solve();
    return 0;
}