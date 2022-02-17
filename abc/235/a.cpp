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
    ll ans = 0;
    ans += (s[0]-'0')*100 + (s[1]-'0')*10 + (s[2]-'0');
    ans += (s[1]-'0')*100 + (s[2]-'0')*10 + (s[0]-'0');
    ans += (s[2]-'0')*100 + (s[0]-'0')*10 + (s[1]-'0');
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}