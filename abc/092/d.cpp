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
    ll A, B; cin >> A >> B;

    // 100x100のグリッドを作り、左半分を黒、右半分を白にする
    vector<string> grid(100);
    for(ll h=0; h<100; h++) {
        for(ll w=0; w<100; w++) {
            if (w < 50) grid[h] += {'#'};
            else grid[h] += {'.'};
        }
    }

    // これで白と黒の連結成分が1個ずつ。
    // 必要な分だけ1x1マスの領域を白や黒に塗る。
    A--; // あと必要な白の連結成分の個数
    for(ll h=0; h<100; h+=2) {
        for(ll w=0; w<=48; w+=2) {
            if (A==0) goto doneA;
            grid[h][w] = '.';
            A--;
        }
    }
doneA:

    B--; // あと必要な黒の連結成分の個数
    for(ll h=0; h<100; h+=2) {
        for(ll w=51; w<100; w+=2) {
            if (B==0) goto doneB;
            grid[h][w] = '#';
            B--;
        }
    }
doneB:

    // 答え出力
    cout << "100 100" << endl;
    for(ll h=0; h<100; h++) {
        cout << grid[h] << endl;
    }
}


int main() {
    solve();
    return 0;
}