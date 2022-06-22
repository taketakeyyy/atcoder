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
    vector<ll>h(3), w(3);
    for(ll i=0; i<3; i++) cin >> h[i];
    for(ll i=0; i<3; i++) cin >> w[i];

    ll ans = 0;
    vector<vector<ll>> masu(3, vector<ll>(3,0));
    for(ll a0=1; a0<=h[0]; a0++) {  // たかだか30回
        for(ll b0=1; b0<=h[0]-a0; b0++) {
            ll c0 = h[0] - a0 - b0;
            if (c0 == 0) continue;
            masu[0][0] = a0;
            masu[0][1] = b0;
            masu[0][2] = c0;

            for(ll a1=1; a1<=h[1]; a1++) {
                for(ll b1=1; b1<=h[1]-a1; b1++) {
                    ll c1 = h[1] - a1 - b1;
                    if (c1 == 0) continue;
                    masu[1][0] = a1;
                    masu[1][1] = b1;
                    masu[1][2] = c1;

                    for(ll a2=1; a2<=h[2]; a2++) {
                        for(ll b2=1; b2<=h[2]-a2; b2++) {
                            ll c2 = h[2] - a2 - b2;
                            if (c2 == 0) continue;
                            masu[2][0] = a2;
                            masu[2][1] = b2;
                            masu[2][2] = c2;

                            // wで検証
                            bool is_ok = true;
                            for(ll j=0; j<3; j++) {
                                ll total = 0;
                                for(ll i=0; i<3; i++) {
                                    total += masu[i][j];
                                }
                                if (w[j] != total) {
                                    is_ok = false;
                                    break;
                                }
                            }

                            if (is_ok) ans++;
                        }
                    }
                }
            }
        }
    }

    // 出力
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}