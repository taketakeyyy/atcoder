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


ll H, W;
vector<vector<ll>> memo;  // (i,j)の通り数
vector<vector<ll>> A;

bool is_inside(ll h, ll w) {
    return (h>=0 && h<H && w>=0 && w<W);
}

void dfs(ll h, ll w) {
    if (memo[h][w] == -1) {
        memo[h][w] = 1;  // 「移動しない」も経路に数える
    }

    // 上下左右へ移動
    for(ll vi=0; vi<4; vi++) {
        ll nh = h + vy[vi];
        ll nw = w + vx[vi];
        if (!is_inside(nh, nw)) continue;
        if (A[h][w] >= A[nh][nw]) continue;
        if (memo[nh][nw] != -1) {
            memo[h][w] += memo[nh][nw];
            memo[h][w] %= MOD;
        }
        else {
            dfs(nh, nw);
            memo[h][w] += memo[nh][nw];
            memo[h][w] %= MOD;
        }
    }
}

// 「移動しない」も経路に含める
void solve() {
    cin >> H >> W;
    A.resize(H);
    memo.resize(H);
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            memo[h].resize(W, -1);
            A[h].resize(W);
            cin >> A[h][w];
        }
    }

    // DFSでmemoを埋める
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            if (memo[h][w] == -1) dfs(h,w);
        }
    }

    // 答えを求めて出力
    ll ans = 0;
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            ans += memo[h][w];
            ans %= MOD;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}