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

// 【n角形メモ】
// * 辺がn本である
// * 頂点がn個である

// 【頂点を数える解法】
// n角形を数えるのは、角っこの頂点を数えればよい。
// 【パターン1】
// ..
// .#
//
// 【パターン2】
// .#
// ##
void solve() {
    ll H, W; cin >> H >> W;
    vector<string> S(H);
    for(ll i=0; i<H; i++) {
        cin >> S[i];
    }

    ll ans = 0;
    for(ll h=0; h<H-1; h++) {
        for(ll w=0; w<W-1; w++) {
            if ((S[h][w]=='.' && S[h][w+1]=='.' && S[h+1][w]=='.' && S[h+1][w+1]=='#') ||
                (S[h][w]=='.' && S[h][w+1]=='.' && S[h+1][w]=='#' && S[h+1][w+1]=='.') ||
                (S[h][w]=='.' && S[h][w+1]=='#' && S[h+1][w]=='.' && S[h+1][w+1]=='.') ||
                (S[h][w]=='#' && S[h][w+1]=='.' && S[h+1][w]=='.' && S[h+1][w+1]=='.') ||
                (S[h][w]=='.' && S[h][w+1]=='#' && S[h+1][w]=='#' && S[h+1][w+1]=='#') ||
                (S[h][w]=='#' && S[h][w+1]=='.' && S[h+1][w]=='#' && S[h+1][w+1]=='#') ||
                (S[h][w]=='#' && S[h][w+1]=='#' && S[h+1][w]=='.' && S[h+1][w+1]=='#') ||
                (S[h][w]=='#' && S[h][w+1]=='#' && S[h+1][w]=='#' && S[h+1][w+1]=='.')) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}

// 【辺を数える解法】
// 罫線を数える
void solve2() {
    ll H, W; cin >> H >> W;
    vector<string> S(H);
    for(ll i=0; i<H; i++) {
        cin >> S[i];
    }

    ll ans = 0;
    // 横方向の罫線を数える
    bool is_seq = false;  // 罫線が連続しているか
    for(ll h=0; h<H-1; h++) {
        for(ll w=0; w<W; w++) {
            if (is_seq && S[h][w]=='.' && S[h+1][w]=='#') continue;
            if (is_seq && S[h][w]=='#' && S[h+1][w]=='.') continue;
            if ((!is_seq && S[h][w]=='.' && S[h+1][w]=='#') ||
                (!is_seq && S[h][w]=='#' && S[h+1][w]=='.')
            ) {
                is_seq = true;
                ans++;
                continue;
            }
            is_seq = false;
        }
    }

    // 縦方向の罫線を数える
    is_seq = false;
    for(ll w=0; w<W-1; w++) {
        for(ll h=0; h<H; h++) {
            if (is_seq && S[h][w]=='.' && S[h][w+1]=='#') continue;
            if (is_seq && S[h][w]=='#' && S[h][w+1]=='.') continue;
            if ((!is_seq && S[h][w]=='.' && S[h][w+1]=='#') ||
                (!is_seq && S[h][w]=='#' && S[h][w+1]=='.')
            ) {
                is_seq = true;
                ans++;
                continue;
            }
            is_seq = false;
        }
    }

    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}