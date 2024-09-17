#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1'000'000'007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    char ab, ac, bc; cin >> ab >> ac >> bc;
    if (ab=='<') {
        if (ac=='<') {
            if (bc=='<') {
                // a b c
                cout << 'B' << endl;
            }
            else {
                // a c b
                cout << 'C' << endl;
            }
        }
        else {// ac=='>'
            if (bc=='<') {
                // cab
                throw("error.");
            }
            else {
                // c a b
                cout << 'A' << endl;
            }
        }
    }
    else { // ba
        if (ac=='<') {
            if (bc=='<') {
                // b a c
                cout << 'A' << endl;
            }
            else {// cb
                // c b a c
                // cout << 'B' << endl;
                throw("error");
            }
        }
        else {//ca
            if (bc=='<') {
                // b c a
                cout << 'C' << endl;
            }
            else {
                // c b a
                cout << 'B' << endl;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}