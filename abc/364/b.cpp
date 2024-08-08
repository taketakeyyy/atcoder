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
    ll H, W; cin >> H >> W;
    ll si, sj; cin >> si >> sj;
    si--; sj--;

    // 座標(h,w)はグリッドの内側に収まっているか？
    auto is_inside = [&](const ll &h, const ll &w) -> bool {
        return h>=0 and h<H and w>=0 and w<W;
    };

    vector<string> grid(H);
    for(ll i=0; i<H; i++) cin >> grid[i];

    string X; cin >> X;

    for(ll i=0; i<(ll)X.size(); i++) {
        if (X[i] == 'U') {
            ll ni = si-1;
            ll nj = sj;
            if (!is_inside(ni,nj)) continue;
            if (grid[ni][nj] != '.') continue;
            si = ni;
            sj = nj;
        }
        else if (X[i] == 'D') {
            ll ni = si+1;
            ll nj = sj;
            if (!is_inside(ni,nj)) continue;
            if (grid[ni][nj] != '.') continue;
            si = ni;
            sj = nj;
        }
        else if (X[i] == 'L') {
            ll ni = si;
            ll nj = sj-1;
            if (!is_inside(ni,nj)) continue;
            if (grid[ni][nj] != '.') continue;
            si = ni;
            sj = nj;
        }
        else if (X[i] == 'R') {
            ll ni = si;
            ll nj = sj+1;
            if (!is_inside(ni,nj)) continue;
            if (grid[ni][nj] != '.') continue;
            si = ni;
            sj = nj;
        }
    }

    cout << si+1 << " " << sj+1 << endl;
}


int main() {
    solve();
    return 0;
}