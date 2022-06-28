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
    ll H, W; cin >> H >> W;
    vector<vector<ll>> A(H, vector<ll>(W, 0));
    vector<vector<ll>> B(H, vector<ll>(W, 0));
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            cin >> A[h][w];
        }
    }
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            cin >> B[h][w];
        }
    }

    // 左上から合わせていく
    ll total = 0;  // 操作回数
    for(ll h=0; h<H-1; h++) {
        for(ll w=0; w<W-1; w++) {
            ll diff = B[h][w] - A[h][w];
            total += abs(diff);
            for(ll i=0; i<2; i++) {
                for(ll j=0; j<2; j++) {
                    A[h+i][w+j] += diff;
                }
            }
        }
    }

    // 合っているか？
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (A[h][w] != B[h][w]) {
                cout << "No" << endl;
                return;
            }
        }
    }
    cout << "Yes" << endl;
    cout << total << endl;
}


int main() {
    solve();
    return 0;
}