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
    ll K; cin >> K;
    if (K==1) {
        cout << "2" << endl;
        return;
    }

    ll i = 0;
    ll len=1;
    ll restK = K-len;
    while(1) {
        i++;
        len = len*2;
        if (restK <= len) {
            string ans = "";
            ll bit = 0 + (restK-1);
            for(ll d=0; d<i; d++) {
                if ((bit>>d)&1) {
                    ans = "2" + ans;
                }
                else {
                    ans = "0" + ans;
                }
            }
            // 出力
            cout << "2" << ans << endl;
            return;
        }
        else {
            restK -= len;
        }
    }
}


int main() {
    solve();
    return 0;
}