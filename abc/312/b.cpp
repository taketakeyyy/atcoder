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


bool is_inside(ll h, ll w, ll N, ll M) {
    return (h>=0 && h<N && w>=0 && w<M);
}

void is_takcode(ll h, ll w, vector<string>& grid, ll N, ll M) {
    bool is_ok = true;
    for(ll i=0; i<9; i++) {
        for(ll j=0; j<9; j++) {
            ll nh = h + i;
            ll nw = w + j;
            if (!is_inside(nh, nw, N, M)) {
                is_ok = false;
                break;
            }

            if (i<3 && j<3) {
                if (grid[nh][nw] != '#') is_ok = false;
            }
            if (i>=6 && j>=6) {
                if (grid[nh][nw] != '#') is_ok = false;
            }
        }
    }

    for(ll i=0; i<4; i++) {
        ll nh = h + i;
        ll nw = w + 3;
        if (!is_inside(nh, nw, N, M)) {
            is_ok = false; break;
        }
        if (grid[nh][nw] != '.') is_ok = false;
    }
    for(ll j=0; j<4; j++) {
        ll nh = h + 3;
        ll nw = w + j;
        if (!is_inside(nh, nw, N, M)) {
            is_ok = false; break;
        }
        if (grid[nh][nw] != '.') is_ok = false;
    }
    for(ll i=5; i<9; i++) {
        ll nh = h + i;
        ll nw = w + 5;
        if (!is_inside(nh, nw, N, M)) {
            is_ok = false; break;
        }
        if (grid[nh][nw] != '.') is_ok = false;
    }
    for(ll j=5; j<9; j++) {
        ll nh = h + 5;
        ll nw = w + j;
        if (!is_inside(nh, nw, N, M)) {
            is_ok = false; break;
        }
        if (grid[nh][nw] != '.') is_ok = false;
    }

    if (is_ok) {
        cout << h+1 << " " << w+1 << endl;
    }
}

void solve() {
    ll N, M; cin >> N >> M;
    vector<string> grid(N);
    for(ll i=0; i<N; i++) {
        cin >> grid[i];
    }

    for(ll i=0; i<N; i++) {
        for(ll j=0; j<M; j++) {
            is_takcode(i, j, grid, N, M);
        }
    }
}


int main() {
    solve();
    return 0;
}