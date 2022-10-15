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


void solve() {
    ll H, W, rs, cs; cin >> H >> W >> rs >> cs;
    // vector<vector<ll>> grid(H, vector<ll>(W, 0));  // H, Wはデカすぎ大丈夫？
    ll N; cin >> N;  // 10^5
    map<ll,vector<ll>> RWall;  // RWall[i] := 行iにある壁の位置
    map<ll,vector<ll>> CWall;  // CWall[i] := 列iにある壁の位置
    for(ll i=0; i<N; i++) {
        ll r, c; cin >> r >> c;
        // grid[r][c] = 1;
        RWall[r].push_back(c);
        CWall[c].push_back(r);
    }
    for(auto [key, ignore]: RWall) {
        sort(RWall[key].begin(), RWall[key].end());
    }
    for(auto [key, ignore]: CWall) {
        sort(CWall[key].begin(), CWall[key].end());
    }

    // クエリ
    {
        ll r = rs, c = cs;
        ll Q; cin >> Q;  // 10^5
        for(ll q=0; q<Q; q++) {
            char d; cin >> d;
            ll l; cin >> l;
            if (d == 'U') {
                ll idx = lower_bound(CWall[c].begin(), CWall[c].end(), r) - CWall[c].begin();
                if (idx == 0) {
                    r = max(r-l, 1LL);
                }
                else {
                    r = max(r-l, CWall[c][idx-1]+1);
                }
            }
            if (d == 'D') {
                ll idx = lower_bound(CWall[c].begin(), CWall[c].end(), r) - CWall[c].begin();
                if (idx == (ll)CWall[c].size()) {
                    r = min(r+l, H);
                }
                else {
                    r = min(r+l, CWall[c][idx]-1);
                }
            }
            if (d == 'L') {
                ll idx = lower_bound(RWall[r].begin(), RWall[r].end(), c) - RWall[r].begin();
                if (idx == 0) {
                    c = max(c-l, 1LL);
                }
                else {
                    c = max(c-l, RWall[r][idx-1]+1);
                }
            }
            if (d == 'R') {
                ll idx = lower_bound(RWall[r].begin(), RWall[r].end(), c) - RWall[r].begin();
                if (idx == (ll)RWall[r].size()) {
                    c = min(c+l, W);
                }
                else {
                    c = min(c+l, RWall[r][idx]-1);
                }
            }
            // 出力
            cout << r << " " << c << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}