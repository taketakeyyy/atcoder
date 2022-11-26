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
    ll H, M; cin >> H >> M;

    while(1) {
        ll A = H/10;
        ll B = H%10;
        ll C = M/10;
        ll D = M%10;

        ll newH = A*10 + C;
        ll newM = B*10 + D;
        if (0<=newH && newH<=23 && 0<=newM && newM<=59) {
            cout << H << " " << M << endl;
            return;
        }

        M++;
        if (M >= 60) {
            M = 0;
            H++;
            if (H>=24) {
                H = 0;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}