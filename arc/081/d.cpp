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
    ll N; cin >> N;
    vector<string> S(2);
    for(int i=0; i<2; i++) cin >> S[i];

    if (S[0].size()==1) {
        cout << 3 << endl;
        return;
    }

    ll ans = 1;
    for(int w=0; w<(int)S[0].size(); w++) {
        if (w==0) {
            if (S[0][0]==S[1][0]) {
                // 縦置き
                ans *= 3;
                ans %= MOD;
            }
            else {
                // 横置き
                ans *= 6;
                ans %= MOD;
                w++;
            }
            continue;
        }

        if (S[0][w-1]!=S[1][w-1]) {
            // 前回が横置き
            if (S[0][w]==S[1][w]) {
                // 今回は縦置き
                continue;
            }
            else {
                // 今回も横置き
                ans *= 3; ans %= MOD;
                w++;
                continue;
            }
        }
        if (S[0][w-1]==S[1][w-1]) {
            // 前回が縦置き
            if (S[0][w]==S[1][w]) {
                // 今回も縦置き
                ans *= 2; ans %= MOD;
                continue;
            }
            else {
                // 今回は横置き
                ans *= 2; ans %= MOD;
                w++;
                continue;
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}