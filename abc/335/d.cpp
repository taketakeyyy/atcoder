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
    ll N; cin >> N;
    vector grid(N, vector(N, -1LL));

    // 左回りに90度回転させる
    auto rotate = [&]() {
        vector ngrid = grid;
        for(ll i=0; i<N; i++) {
            for(ll j=0; j<N; j++) {
                ngrid[N-1-j][i] = grid[i][j];
            }
        }
        swap(grid, ngrid);
    };

    ll s=0, t=N;
    ll row = 0;
    ll number = 1;
    while(1) {
        if (grid[row][s] != -1) {
            s++; t--;
            row++;
        }
        if (row == (N+1)/2-1) break;

        for(ll j=s; j<t-1; j++) {
            grid[row][j] = number++;
        }
        rotate();
    }

    // 答え
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (grid[i][j] == -1) {
                cout << 'T' << " ";
            }
            else {
                cout << grid[i][j] << " ";
            }
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}