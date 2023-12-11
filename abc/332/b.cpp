#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll K, G, M; cin >> K >> G >> M;
    ll glass = 0;
    ll mag = 0;
    for(ll k=0; k<K; k++) {
        if (glass == G) {
            glass = 0;
        }
        else if (mag == 0) {
            mag = M;
        }
        else {
            if (G-glass < mag) {
                mag -= (G-glass);
                glass = G;
            }
            else {
                glass += mag;
                mag = 0;
            }
        }
    }
    cout << glass << " " << mag << endl;
}


int main() {
    solve();
    return 0;
}