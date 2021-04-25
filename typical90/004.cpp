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
    vector<vector<ll>> A(H, vector<ll>(W, 0));
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            cin >> A[h][w];
        }
    }

    // 各行・列の合計を予め計算しておく
    vector<ll> rH(H,0);
    vector<ll> rW(W,0);
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            rH[h] += A[h][w];
        }
    }
    for(int w=0; w<W; w++) {
        for(int h=0; h<H; h++) {
            rW[w] += A[h][w];
        }
    }

    // 出力
    for(int h=0; h<H; h++) {
        for(int w=0; w<W; w++) {
            cout << rH[h]+rW[w]-A[h][w];
            if (w!=W-1) cout << " ";
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}