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
    ll N; cin >> N;
    string S; cin >> S;

    ll ans = 0;
    ll start = 0;
    char sc = S[start];
    for(ll i=1; i<N; i++) {
        if (S[i] == sc) continue;
        ans += (N-i) * (i - start);
        start = i;
        sc = S[start];
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}