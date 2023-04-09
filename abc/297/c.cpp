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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll H, W; cin >> H >> W;
    vector<string> S(H);
    for(ll i=0; i<H; i++) {
        cin >> S[i];
    }

    // 貪欲にやるだけ
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W-1; w++) {
            if (S[h][w] == 'T' && S[h][w+1] == 'T') {
                S[h][w] = 'P';
                S[h][w+1] = 'C';
                w++;
                continue;
            }
        }
    }

    // 出力
    for(ll h=0; h<H; h++) {
        cout << S[h] << endl;
    }
}


int main() {
    solve();
    return 0;
}