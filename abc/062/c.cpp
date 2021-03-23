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
    ll H, W; cin >> H >> W;
    // チョコバーの分割の仕方は、必ず長方形にする必要があるので、
    // (1) 横3
    // (2) 横1、縦2
    // の2種類ある。それぞれについて最小値を求める。

    ll ans = INF;
    // Hを3分割する方法
    if (H%3==0) {
        cout << 0 << endl;
        return;
    }
    else if (H%3==1) {
        ll h1 = H/3;
        ll h2 = H/3;
        ll h3 = H/3+1;
        ll mx = max(W*h1, max(W*h2, W*h3));
        ll mn = min(W*h1, min(W*h2, W*h3));
        ans = min(ans, mx-mn);
    }
    else if (H%3==2) {
        ll h1 = H/3;
        ll h2 = H/3+1;
        ll h3 = H/3+1;
        ll mx = max(W*h1, max(W*h2, W*h3));
        ll mn = min(W*h1, min(W*h2, W*h3));
        ans = min(ans, mx-mn);
    }
    // Wを3分割する方法
    if (W%3==0) {
        cout << 0 << endl;
        return;
    }
    else if(W%3==1) {
        ll w1 = W/3;
        ll w2 = W/3;
        ll w3 = W/3+1;
        ll mx = max(H*w1, max(H*w2, H*w3));
        ll mn = min(H*w1, min(H*w2, H*w3));
        ans = min(ans, mx-mn);
    }
    else if(W%3==2) {
        ll w1 = W/3;
        ll w2 = W/3+1;
        ll w3 = W/3+1;
        ll mx = max(H*w1, max(H*w2, H*w3));
        ll mn = min(H*w1, min(H*w2, H*w3));
        ans = min(ans, mx-mn);
    }

    // 横1、縦2に分割する方法
    if (H%2==0) {
        // H側を2分割できる方法
        ll h = H/2;
        for(int w=1; w<W; w++) {
            ans = min(ans, abs(h*w - H*(W-w)));
        }
    }
    else {
        // H側を2分割するが、片方の長さが1大きいパターン
        ll h1 = H/2;
        ll h2 = H/2+1;
        for(int w=1; w<W; w++) {
            ll mx = max(h1*w, max(h2*w, H*(W-w)));
            ll mn = min(h1*w, min(h2*w, H*(W-w)));
            ans = min(ans, mx-mn);
        }
    }


    if (W%2==0) {
        // W側を2分割できる方法
        ll w = W/2;
        for(int h=1; h<H; h++) {
            ans = min(ans, abs(h*w - W*(H-h)));
        }
    }
    else {
        // W側を2分割するが、片方の長さが1大きいパターン
        ll w1 = W/2;
        ll w2 = W/2+1;
        for(int h=1; h<H; h++) {
            ll mx = max(h*w1, max(h*w2, W*(H-h)));
            ll mn = min(h*w1, min(h*w2, W*(H-h)));
            ans = min(ans, mx-mn);
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}