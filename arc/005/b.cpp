#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


pair<ll,ll> move(string& ans, const vector<string>& grid, string& W, ll x, ll y) {
    ll nx, ny;
    if (W=="R") {
        if (x+1 == 9) {
            nx = x-1;
            W = "L";
        }
        else {
            nx = x+1;
        }
        ny = y;
    }
    else if (W=="L") {
        if (x-1==-1) {
            nx = x+1;
            W = "R";
        }
        else {
            nx = x-1;
        }
        ny = y;
    }
    else if (W=="U") {
        if (y-1==-1) {
            ny = y+1;
            W = "D";
        }
        else {
            ny = y-1;
        }
        nx = x;
    }
    else if (W=="D"){
        if (y+1==9) {
            ny = y-1;
            W = "U";
        }
        else {
            ny = y+1;
        }
        nx = x;
    }
    else if (W=="RU") {
        if (x+1<9 && y-1==-1) {
            // 上に当たった
            ny = y+1;
            nx = x+1;
            W = "RD";
        }
        else if (x+1==9 && y-1>-1) {
            // 右に当たった
            ny = y-1;
            nx = x-1;
            W = "LU";
        }
        else if (x+1==9 && y-1==-1) {
            // 右上に当たった
            ny = y+1;
            nx = x-1;
            W = "LD";
        }
        else {
            ny = y-1;
            nx = x+1;
        }
    }
    else if (W=="RD") {
        if (x+1<9 && y+1==9) {
            // 下に当たった
            ny = y-1;
            nx = x+1;
            W = "RU";
        }
        else if (x+1==9 && y+1<9) {
            // 右に当たった
            ny = y+1;
            nx = x-1;
            W = "LD";
        }
        else if (x+1==9 && y+1==9) {
            // 右下に当たった
            ny = y-1;
            nx = x-1;
            W = "LU";
        }
        else {
            ny = y+1;
            nx = x+1;
        }
    }
    else if (W=="LU") {
        if (x-1>-1 && y-1==-1) {
            // 上に当たった
            ny = y+1;
            nx = x-1;
            W = "LD";
        }
        else if (x-1==-1 && y-1>-1) {
            // 左に当たった
            ny = y-1;
            nx = x+1;
            W = "RU";
        }
        else if (x-1==-1 && y-1==-1) {
            // 左上に当たった
            ny = y+1;
            nx = x+1;
            W = "RD";
        }
        else {
            ny = y-1;
            nx = x-1;
        }
    }
    else if (W=="LD") {
        if (x-1>-1 && y+1==9) {
            // 下に当たった
            ny = y-1;
            nx = x-1;
            W = "LU";
        }
        else if (x-1==-1 && y+1<9) {
            // 左に当たった
            ny = y+1;
            nx = x+1;
            W = "RD";
        }
        else if (x-1==-1 && y+1==9) {
            // 左下に当たった
            ny = y-1;
            nx = x+1;
            W = "RU";
        }
        else {
            ny = y+1;
            nx = x-1;
        }
    }
    ans += grid[ny][nx];
    return make_pair(nx, ny);
}

void solve() {
    ll x, y; string W; cin >> x >> y >> W;
    x--; y--;
    vector<string>grid(9);
    for(int i=0; i<9; i++) {
        cin >> grid[i];
    }

    // シミュレーションする
    string ans = "";
    ans += grid[y][x];
    for(int i=0; i<3; i++) {
        tie(x, y) = move(ans, grid, W, x, y);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}