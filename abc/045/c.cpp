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
    ll N = S.size() - 1;
    ll ans = 0;
    for(ll bit=0; bit<1<<N; bit++) {
        ll total = 0;
        ll l=0;
        for(ll d=0; d<N; d++) {
            if (bit>>d&1) {
                string s = S.substr(l, d-l+1);
                total += stoll(s);
                l = d+1;
            }
        }
        string s = S.substr(l, S.size()-l);
        total += stoll(s);
        ans += total;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}