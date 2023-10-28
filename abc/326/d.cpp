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

ll N;
string R, C;

bool is_ok_grid(vector<vector<char>> &grid) {
    // Cの検証
    for(ll w=0; w<N; w++) {
        for(ll h=0; h<N; h++) {
            if (grid[h][w]=='.') continue;
            if (grid[h][w] == C[w]) {
                break;
            }
            return false;
        }
    }

    {// 各列のABCの個数の検証
        for(ll w=0; w<N; w++) {
            map<char,ll> mp;
            for(ll h=0; h<N; h++) {
                mp[grid[h][w]]++;
            }
            if (!(mp['A']==1&&mp['B']==1&&mp['C']==1)) return false;
        }
    }

    return true;
}


// 行と列を独立に考えるに近いかも
// 各行をnext_permutationで作って検証
// 全部埋めたら、各列を検証
void dfs(ll h, vector<vector<char>> &grid, vector<vector<bool>> &col_used) {
    // 終了条件
    if (h == N) {
        if (is_ok_grid(grid)) {
            // 出力して終了
            cout << "Yes" << endl;
            for(ll h=0; h<N; h++) {
                for(ll w=0; w<N; w++) {
                    cout << grid[h][w];
                }
                cout << endl;
            }
            exit(0);
        }
        else {
            return;
        }
    }

    // 探索
    vector<char> abc = {'A','B','C'};
    for(ll i=3; i<N; i++) abc.push_back('.');
    sort(abc.begin(), abc.end());
    do { // "ABC.."の順列を回す
        { // w列目に使って良い文字だけ使えているか？
            bool is_ok = true;
            for(ll w=0; w<N; w++) {
                if (abc[w]!='.') {
                    if (col_used[w][abc[w]-'A']) is_ok = false;
                }
            }
            if (!is_ok) continue;
        }

        {// abcの最初の文字はR[h]か？
            bool is_ok = true;
            for(ll w=0; w<N; w++) {
                if (abc[w]=='.') continue;
                if (abc[w]!=R[h]) is_ok = false;
                break;
            }
            if (!is_ok) continue;
        }

        for(ll w=0; w<N; w++) grid[h][w] = abc[w];
        for(ll w=0; w<N; w++) if (abc[w]!='.') col_used[w][abc[w]-'A'] = true;
        dfs(h+1, grid, col_used);
        for(ll w=0; w<N; w++) if (abc[w]!='.') col_used[w][abc[w]-'A'] = false;
        for(ll w=0; w<N; w++) grid[h][w] = '.';
    }while (next_permutation(abc.begin(), abc.end()));
}

void solve() {
    cin >> N;
    cin >> R >> C;

    vector col_used(N, vector<bool>(3, false)); // col_used[w][i] := w列目において、'A'+i の文字はすでに使っているか？
    vector grid(N, vector<char>(N, '.'));
    dfs(0, grid, col_used);
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}