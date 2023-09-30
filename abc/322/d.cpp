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


// 11x11マスに拡張させて、全探索する
void solve() {
    vector<vector<vector<char>>> P(3, vector<vector<char>>(4, vector<char>(4)));
    for(ll i=0; i<4; i++) {
        for(ll j=0; j<4; j++) {
            cin >> P[0][i][j];
        }
    }
    for(ll i=0; i<4; i++) {
        for(ll j=0; j<4; j++) {
            cin >> P[1][i][j];
        }
    }
    for(ll i=0; i<4; i++) {
        for(ll j=0; j<4; j++) {
            cin >> P[2][i][j];
        }
    }

    // それぞれ回転させる
    vector<vector<vector<vector<char>>>> newPs(3);
    for(ll p=0; p<3; p++) {
        vector<vector<char>> newP(4, vector<char>(4));
        auto nowP = P[p];
        for(ll cnt=0; cnt<4; cnt++) {
            // 回転
            ll nj = 0;
            for(ll i=0; i<4; i++) {
                ll ni = 3;
                for(ll j=0; j<4; j++) {
                    newP[ni][nj] = nowP[i][j];
                    ni--;
                }
                nj++;
            }
            newPs[p].push_back(newP);
            nowP = newP;
        }
    }

    // 11x11マスのグリッド内に収まっているか？
    auto is_inside = [&](ll i, ll j) -> bool {
        return (i>=0 && i<11 && j>=0 && j<11);
    };

    // 中央の[3,6]区間に入っているか？
    auto is_inner = [&](ll i, ll j) -> bool {
        return (i>=3 && i<=6 && j>=3 && j<=6);
    };

    // Aは座標(i,j)から置けるか？
    auto can_put = [&](ll i, ll j, vector<vector<char>>&grid, vector<vector<char>>&A) -> bool {
        for(ll ni=0; ni<4; ni++) {
            for(ll nj=0; nj<4; nj++) {
                if (A[ni][nj]=='#' && !is_inner(i+ni, j+nj)) {
                    return false;
                }
                if (!is_inside(i+ni, j+nj)) {
                    return false;
                }
                if (grid[i+ni][j+nj]=='#' && A[ni][nj]=='#') {
                    return false;
                }
            }
        }
        return true;
    };

    // Aを置く
    auto put = [&](ll i, ll j, vector<vector<char>>&grid, vector<vector<char>>&A) -> void {
        for(ll ni=0; ni<4; ni++) {
            for(ll nj=0; nj<4; nj++) {
                if (A[ni][nj] == '#') grid[i+ni][j+nj] = A[ni][nj];
            }
        }
    };

    // Aを置く前に戻す
    auto unput = [&](ll i, ll j, vector<vector<char>>&grid, vector<vector<char>>&A) -> void {
        for(ll ni=0; ni<4; ni++) {
            for(ll nj=0; nj<4; nj++) {
                if (A[ni][nj] == '#') {
                    grid[i+ni][j+nj] = '.';
                }
            }
        }
    };

    // 正しく置けたか？
    auto is_valid = [&](vector<vector<char>>&grid) -> bool {
        for(ll i=0; i<11; i++) {
            for(ll j=0; j<11; j++) {
                if (i>=3 && i<=6 && j>=3 && j<=6) {
                    if (grid[i][j] == '#') continue;
                    return false;
                }
                else {
                    if (grid[i][j] == '.') continue;
                    return false;
                }
            }
        }
        return true;
    };

    // ポリオミノを置ける場所を再帰的に探す
    auto dfs = [&](auto dfs, ll p, vector<vector<char>> &grid) -> bool {
        // 終了条件
        if (p == 3) {
            return is_valid(grid);
        }

        for(ll c=0; c<4; c++) {
            for(ll i=0; i<11; i++) {
                for(ll j=0; j<11; j++) {
                    if (can_put(i, j, grid, newPs[p][c])) {
                        put(i, j, grid, newPs[p][c]);
                        bool res = dfs(dfs, p+1, grid);
                        if (res) return true;
                        unput(i, j, grid, newPs[p][c]);
                    }
                }
            }
        }
        return false;
    };

    // デバッグ用出力
    auto output = [&](vector<vector<char>> &grid) {
        for(ll i=0; i<11; i++) {
            for(ll j=0; j<11; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
    };

    // 全探索
    vector<vector<char>> grid(11, vector<char>(11, '.'));
    if (dfs(dfs, 0, grid)) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}