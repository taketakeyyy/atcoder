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
    ll H, W, N; cin >> H >> W >> N;
    vector grid(H, vector(W, 0LL));
    ll now_i = 0;
    ll now_j = 0;
    ll now_dir = 0;

    auto move = [&](ll &i, ll &j, ll &dir) {
        i += vy[dir];
        j += vx[dir];
        if (i < 0) i = H-1;
        if (j < 0) j = W-1;
        if (i == H) i = 0;
        if (j == W) j = 0;
    };

    for(ll n=0; n<N; n++) {
        if (grid[now_i][now_j]==0) {
            // 現在いるマスが白なら
            grid[now_i][now_j] = 1;
            now_dir++; now_dir%=4;
            move(now_i, now_j, now_dir);
        }
        else {
            // 現在いるマスが黒なら
            grid[now_i][now_j] = 0;
            now_dir--;
            if (now_dir<0)now_dir=3;
            move(now_i, now_j, now_dir);
        }
    }

    // 出力
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (grid[h][w]==0) cout << '.';
            else cout << '#';
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}