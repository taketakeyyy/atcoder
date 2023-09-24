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
vector<ll> vvy = { 0, -1, 0, 1, 0 };
vector<ll> vvx = { 0, 0, 1, 0, -1 };


class Solver {
private:
    // 座標がグリッド内に収まっているか？
    bool is_inside(ll h, ll w) {
        return (h>=0 && h<mN+2 && w>=0 && w<mN+2);
    }

public:
    ll mN, mM; // 50, 100 固定
    vector<vector<ll>> m_grid; // (N+2)x(N+2)のグリッド（最外周は0埋め）
    vector<vector<bool>> m_is_neighbor; // m_is_neighbor[c][d] := 色cは色dと隣接しているか？
    vector<vector<ll>> m_neighbor; // m_neighbor[c] := 色cと隣接している色リスト
    vector<vector<ll>> m_ans_grid;
    vector<ll> m_color_num; // m_color_num[c] := 色cのマスの数
    Solver() {

    }

    // 標準入力を受け取り、必要なデータ構造を構築する
    void input_and_build() {
        cin >> mN >> mM;
        m_grid.resize(mN+2);
        for(ll i=0; i<=mN+1; i++) {
            m_grid[i].resize(mN+2, 0);
        }
        for(ll i=1; i<=mN; i++) {
            for(ll j=1; j<=mN; j++) {
                cin >> m_grid[i][j];
            }
        }
        m_is_neighbor.resize(mM+1);
        for(ll c=0; c<=mM; c++) m_is_neighbor[c].resize(mM+1, false);
        for(ll c=0; c<=mM; c++) {
            m_is_neighbor[c][c] = true;
        }

        // 隣接関係を構築する
        m_neighbor.resize(mM+1);
        for(ll i=0; i<mN+2; i++) {
            for(ll j=0; j<mN+2; j++) {
                ll c = m_grid[i][j];
                for(ll vi=0; vi<4; vi++) {
                    ll ni = i + vy[vi];
                    ll nj = j + vx[vi];
                    if (!is_inside(ni, nj)) continue;
                    ll nc = m_grid[ni][nj];
                    if (m_is_neighbor[c][nc]) continue;
                    m_is_neighbor[c][nc] = true;
                    m_is_neighbor[nc][c] = true;
                    m_neighbor[c].push_back(nc);
                    m_neighbor[nc].push_back(c);
                }
            }
        }

        // m_color_num構築
        m_color_num.resize(mM+1, 0);
        for(ll i=0; i<mN+2; i++) {
            for(ll j=0; j<mN+2; j++) {
                ll c = m_grid[i][j];
                m_color_num[c]++;
            }
        }

        // 答え用のグリッド
        m_ans_grid = m_grid;
    }

    // 現在のグリッドを、隣接条件が崩れないように0に塗っていく
    void greedy_plan() {
        // (si,sj)マスの連結が崩れてないかチェックする
        auto link_check = [&](ll si, ll sj) -> bool {
            ll target_c = m_ans_grid[si][sj];
            deque<pair<ll,ll>> deq; deq.push_back({si,sj});
            set<pair<ll,ll>> visited; visited.insert({si,sj});
            ll num = 1; // 色の数
            set<ll> neibor; // 隣接している色の集合

            // BFSで同じ色のマスを探索する
            while(!deq.empty()) {
                auto[i, j] = deq.front(); deq.pop_front();

                for(ll vi=0; vi<4; vi++) {
                    ll ni = i + vy[vi];
                    ll nj = j + vx[vi];
                    if (!is_inside(ni, nj)) continue;
                    neibor.insert(m_ans_grid[ni][nj]);
                    if (m_ans_grid[ni][nj] != target_c) continue;
                    if (visited.count({ni,nj})) continue;
                    visited.insert({ni,nj});
                    num++;
                    deq.push_back({ni,nj});
                }
            }

            // 隣接すべきものと隣接しているか？
            for(ll c: m_neighbor[target_c]) {
                if(neibor.count(c)) continue;
                return false;
            }

            // 数が一致していたら連結している
            bool res = (m_color_num[target_c]==num);
            return res;
        };

        // (i,j)の隣接4マスは0と隣接してOKかチェックする
        auto check_next_to_zero = [&](ll i, ll j) -> bool {
            for(ll vi=0; vi<4; vi++) {
                ll ni = i + vy[vi];
                ll nj = j + vx[vi];
                if (!is_inside(ni,nj)) continue;
                if (m_is_neighbor[m_ans_grid[ni][nj]][0]) continue;
                return false;
            }
            return true;
        };

        // 白に塗れるマスは貪欲に白に塗っていく
        while(1) {
            bool is_change = false; // 1回でも白く塗れた？
            for(ll i=1; i<=mN; i++) {
                for(ll j=1; j<=mN; j++) {
                    ll target_c = m_ans_grid[i][j]; // 今回のターゲット（白く塗るやつ）
                    if (target_c == 0) continue;
                    if (m_color_num[target_c] == 1) continue; // 残り1個の色は塗ったらだめでしょ
                    // 周囲4マスは0と隣接してOK？
                    if (!check_next_to_zero(i, j)) continue;

                    // 自身と周囲4マスの連結が崩れてないか？
                    m_ans_grid[i][j] = 0; // 一時的に白に塗っておく
                    m_color_num[target_c]--;
                    m_color_num[0]++;
                    bool is_ok = true;
                    for(ll vi=0; vi<4; vi++) {
                        ll ni = i + vvy[vi];
                        ll nj = j + vvx[vi];
                        if (!is_inside(ni, nj)) continue;

                        // 隣接する4マスの色の隣接条件が崩れないかチェックする
                        // if (m_ans_grid[ni][nj] == 0) continue;
                        if (link_check(ni,nj)) continue;
                        // 0に塗ったら駄目だった
                        is_ok = false;
                        break;
                    }

                    if (is_ok) {
                        is_change = true;
                    }
                    else {
                        // 一時的に塗ったものをもとに戻す
                        m_ans_grid[i][j] = target_c;
                        m_color_num[target_c]++;
                        m_color_num[0]--;
                    }
                }
            }

            if (!is_change) break;
        }
    }

    // 答えを出力する
    void output() {
        for(ll i=1; i<=mN; i++) {
            for(ll j=1; j<=mN; j++) {
                if (j == mN) cout << m_ans_grid[i][j] << endl;
                else cout << m_ans_grid[i][j] << " ";
            }
        }
    }

    // 実行
    void run() {
        input_and_build();
        greedy_plan();
        output();
    }
};

void solve() {
    Solver solver = Solver();
    solver.run();
}


int main() {
    solve();
    return 0;
}