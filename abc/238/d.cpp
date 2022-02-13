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
    ll T; cin >> T;
    for (ll t=0; t<T; t++) {
        ll a, s;
        cin >> a >> s;

        bool is_ok = true;
        vector<ll> xdp(61, 0);
        vector<ll> ydp(61, 0);
        vector<ll> cdp(62, 0); // 桁上り用
        for (ll d=0; d<61; d++) {
            if ((a>>d)&1) {
                xdp[d] = 1;
                ydp[d] = 1;
                if ((s>>d)&1) {
                    if (cdp[d]==1) {
                        cdp[d+1] = 1;
                    }
                    else {
                        is_ok = false;
                        break;
                    }
                }
                else {
                    if (cdp[d]==1) {
                        is_ok = false;
                        break;
                    }
                    else {
                        cdp[d+1] = 1;
                    }
                }
            }
            else {
                if ((s>>d)&1) {
                    if (cdp[d]==1) {
                        xdp[d] = 0;
                        ydp[d] = 0;
                    }
                    else {
                        xdp[d] = 0;
                        ydp[d] = 1;
                    }
                }
                else {
                    if (cdp[d]==1) {
                        xdp[d] = 0;
                        ydp[d] = 1;
                        cdp[d+1] = 1;
                    }
                    else {
                        xdp[d] = 0;
                        ydp[d] = 0;
                    }
                }
            }
        }

        if (is_ok) {
            // 実際にxとyを作ってみて、正しい計算になるか確認
            ll x = 0;
            ll base = 1;
            for(ll d=0; d<61; d++) {
                if (xdp[d]==1) {
                    x += base;
                }
                base *= 2;
            }
            ll y = 0;
            base = 1;
            for(ll d=0; d<61; d++) {
                if (ydp[d]==1) {
                    y += base;
                }
                base *= 2;
            }

            if ((x&y)==a && (x+y)==s) {
                cout << "Yes" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
        else {
            cout << "No" << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}