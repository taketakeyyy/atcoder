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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector grid(101, vector<bool>(101, false));
    for(ll i=0; i<N; i++) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        for(ll x=a; x<b; x++) {
            for(ll y=c; y<d; y++) {
                grid[x][y] = true;
            }
        }
    }

    ll ans = 0;
    for(ll i=0; i<101; i++) {
        for(ll j=0; j<101; j++) {
            if (grid[i][j]) ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}