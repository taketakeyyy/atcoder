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
string vs = "URDL";  // 右下
vector<ll> vy = { 0, 1 };
vector<ll> vx = { 1, 0 };

ll H, W;
vector<vector<ll>> A;
ll ans = 0;

bool is_inside(ll h, ll w) {
    return (h>=0 && h<H && w>=0 && w<W);
}

void dfs(ll h, ll w, set<ll> &visited) {
    if (h==H-1 && w==W-1) {
        ans++;
        return;
    }

    for(ll vi=0; vi<2; vi++) {
        ll nh = h + vy[vi];
        ll nw = w + vx[vi];
        if (!is_inside(nh, nw)) continue;
        if (visited.count(A[nh][nw])) continue;
        visited.insert(A[nh][nw]);
        dfs(nh,nw,visited);
        visited.erase(A[nh][nw]);
    }
}

void solve() {
    cin >> H >> W;
    A.resize(H);
    for(ll i=0; i<H; i++) {
        A[i].resize(W);
        for(ll j=0; j<W; j++) cin >> A[i][j];
    }

    set<ll> visited;
    visited.insert(A[0][0]);
    dfs(0,0,visited);

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}