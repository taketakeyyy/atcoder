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

const ll N = 50;
vector<ll> vy = {1, 0, -1, 0};
vector<ll> vx = {0, 1, 0, -1};
string vs = "DRUL";

/**
 * @brief 座標x,yがタイルの内側に収まっているかの判定
 *
 * @param y
 * @param x
 * @return true
 * @return false
 */
bool inside(ll y, ll x) {
    return y>=0 && x>=00 && y<N && x<N;
}

void solve() {
    ll si, sj; cin >> si >> sj;
    vector<vector<ll>> tiles(N, vector<ll>(N, 0));
    vector<vector<ll>> points(N, vector<ll>(N, 0));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> tiles[i][j];
        }
    }
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            cin >> points[i][j];
        }
    }

    vector<bool> used = vector<bool>(N*N);  // 訪問済みタイル番号
    used[tiles[si][sj]] = true;
    string ans = "";

    // 幅優先的にやる
    ll y = si;
    ll x = sj;
    ll point = tiles[si][sj];
    while (1) {
        ll next_move = -1;  // vy, vx, vs の添字
        ll next_point = point;

        for(ll k=0; k<4; k++) {
            ll ny = y + vy[k];
            ll nx = x + vx[k];
            if (!inside(ny, nx)) continue;
            if (used[tiles[ny][nx]]) continue;
            if (next_point > point + points[ny][nx]) continue;
            next_move = k;
            next_point = point + points[ny][nx];
        }

        if (next_move == -1) break;
        y = y + vy[next_move];
        x = x + vx[next_move];
        used[tiles[y][x]] = true;
        point += points[y][x];
        ans += vs[next_move];
    }

    // 出力
    printf("%s\n", ans.c_str());
}


int main() {
    solve();
    return 0;
}