#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    ll H, W; cin >> H >> W;
    vector<vector<ll>> P(H, vector<ll>(W, 0));
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            cin >> P[h][w];
        }
    }

    ll ans = 0;
    // 変量の少ないHをbit全探索
    for(ll bit=0; bit<(1<<H); bit++) {
        map<ll,ll> Map;
        for(ll w=0; w<W; w++) {
            ll hv = -1;
            bool flag = true;
            ll count = 0;
            for(ll h=0; h<H; h++) {
                if (bit>>h&1) {
                    if (hv==-1) {
                        hv = P[h][w];
                        count++;
                    }
                    else if (P[h][w]!=hv){
                        flag = false;
                        break;
                    }
                    else {
                        count++;
                    }
                }
            }
            if (flag) {
                Map[hv] += count++;
            }
        }

        for(auto [key, value]: Map) {
            ans = max(ans, value);
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}