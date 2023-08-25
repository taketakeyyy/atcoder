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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// TLE
// 愚直なシミュレーション解
void solve() {
    ll H, W; cin >> H >> W;
    vector<string> org_grid(H);
    for(ll i=0; i<H; i++) {
        cin >> org_grid[i];
    }

    vector<vector<char>> grid(H, vector<char>(W));
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            grid[i][j] = org_grid[i][j];
        }
    }
    while(1) {
        if (grid.size()<=1 || grid[0].size()<=1) break;
        bool is_change = false;

        // 各行を調べる
        vector<bool> cols(grid.size(), false);
        for(ll h=0; h<(ll)grid.size(); h++) {
            bool is_same = true;
            for(ll w=1; w<(ll)grid[0].size(); w++) {
                if (grid[h][0] != grid[h][w]) {
                    is_same = false;
                    break;
                }
            }
            if (is_same) {
                is_change = true;
                cols[h] = true;
            }
        }

        // 各列調べる
        vector<bool> rows(grid[0].size(), false);
        for(ll w=0; w<(ll)grid[0].size(); w++) {
            bool is_same = true;
            for(ll h=1; h<(ll)grid.size(); h++) {
                if (grid[0][w] != grid[h][w]) {
                    is_same = false;
                    break;
                }
            }
            if (is_same) {
                is_change = true;
                rows[w] = true;
            }
        }

        // 変化なしなら終了
        if (!is_change) break;

        // 新しいgridを作る
        vector<vector<char>> new_grid;
        ll i=0;
        for(ll h=0; h<(ll)grid.size(); h++) {
            if (cols[h]) continue;
            new_grid.push_back(vector<char>());
            for(ll w=0; w<(ll)grid[0].size(); w++) {
                if (rows[w]) continue;
                new_grid[i].push_back(grid[h][w]);
            }
            i++;
        }
        grid = new_grid;
    }

    // クッキーの枚数を調べる
    ll ans = grid.size() * grid[0].size();
    cout << ans << endl;
}


// AC
// 英小文字は26個しかないことを利用する
void solve2() {
    ll H, W; cin >> H >> W;
    vector<string> org_grid(H);
    for(ll i=0; i<H; i++) {
        cin >> org_grid[i];
    }

    vector rows(H, vector<ll>(26, 0));  // rows[h][i] := h行の文字iの数（各行の分布）
    for(ll h=0; h<H; h++) {
        for(ll w=0; w<W; w++) {
            ll c = org_grid[h][w]-'a';
            rows[h][c]++;
        }
    }

    vector cols(W, vector<ll>(26, 0));  // cols[w][i] := w列の文字iの数（各列の分布）
    for(ll w=0; w<W; w++) {
        for(ll h=0; h<H; h++) {
            ll c = org_grid[h][w]-'a';
            cols[w][c]++;
        }
    }

    ll del_row = 0; // 削除した行の数
    ll del_col = 0; // 削除した列の数
    while(1) {
        bool is_changed = false;

        // 行を消す作業 O(H) 高々H+W回繰り返す
        ll cnt_row = 0; // 消える行の数
        vector<ll> del_h;
        if (W-del_col >= 2) {
            for(ll h=0; h<H; h++) {
                for(ll c=0; c<26; c++) {
                    if (rows[h][c] == W-del_col) {
                        is_changed = true;
                        cnt_row++;
                        del_h.push_back(h);
                    }
                }
            }
        }

        // 列を消す作業 O(W) 高々H+W回繰り返す
        ll cnt_col = 0; // 消える列の数
        vector<ll> del_w;
        if (H-del_row >= 2) {
            for(ll w=0; w<W; w++) {
                for(ll c=0; c<26; c++) {
                    if (cols[w][c] == H-del_row) {
                        is_changed = true;
                        cnt_col++;
                        del_w.push_back(w);
                    }
                }
            }
        }

        // 削除する作業
        if (!is_changed) break;
        del_col += cnt_col;
        del_row += cnt_row;
        for(ll h: del_h) { // 高々H回
            for(ll w=0; w<W; w++) {
                rows[h][org_grid[h][w]-'a'] = max(0LL, rows[h][org_grid[h][w]-'a']-1LL);
                cols[w][org_grid[h][w]-'a'] = max(0LL, cols[w][org_grid[h][w]-'a']-1LL);
            }
        }
        for(ll w: del_w) { // 高々W回
            for(ll h=0; h<H; h++) {
                rows[h][org_grid[h][w]-'a'] = max(0LL, rows[h][org_grid[h][w]-'a']-1LL);
                cols[w][org_grid[h][w]-'a'] = max(0LL, cols[w][org_grid[h][w]-'a']-1LL);
            }
        }
    }

    // 答えを数える
    ll ans = (H-del_row) * (W-del_col);
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}