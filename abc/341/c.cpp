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
    string T; cin >> T;
    vector<string> grid(H);
    for(ll h=0; h<H; h++) {
        cin >> grid[h];
    }

    auto can_move = [&](ll si, ll sj) -> bool {
        ll now_h = si;
        ll now_w = sj;
        for(ll i=0; i<N; i++) {
            if (T[i]=='L') now_w--;
            else if (T[i]=='R') now_w++;
            else if (T[i]=='U') now_h--;
            else now_h++;

            if (grid[now_h][now_w]=='#') return false;
        }
        return true;
    };

    // 全探索
    ll ans = 0;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (grid[h][w]=='#') continue;
            if (can_move(h,w)) ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}