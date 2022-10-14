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

ll N, M;
vector<vector<ll>> grid;

bool is_inside(ll n, ll m) {
    return (n>=0 && n<N && m>=0 && m<M);
}

void dfs(ll n, ll m, ll depth, ll &ans) {
    for(ll vi=0; vi<4; vi++) {
        ll nn = n + vy[vi];
        ll nm = m + vx[vi];
        if (is_inside(nn,nm) && grid[nn][nm]==1) {
            grid[nn][nm] = 0;
            dfs(nn, nm, depth+1, ans);
            grid[nn][nm] = 1;
        }
    }

    ans = max(ans, depth);
}

// 移動方法は200,000を超えない上、時間制限10sec
// 全てのマス90*90 = 8100 でDFSしても間に合う
void solve() {
    cin >> M >> N;
    grid.resize(N);
    for(ll n=0; n<N; n++) {
        grid[n].resize(M);
        for(ll m=0; m<M; m++) {
            cin >> grid[n][m];
        }
    }

    // 全てのマスにおいてDFSしても間に合う
    ll ans = 0;
    for(ll n=0; n<N; n++) {
        for(ll m=0; m<M; m++) {
            if (grid[n][m] == 1) {
                grid[n][m] = 0;
                dfs(n,m,1,ans);
                grid[n][m] = 1;
            }
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}