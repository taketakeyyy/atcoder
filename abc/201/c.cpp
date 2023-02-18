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

/**
 * @brief 二項係数C(n,r)
 * @details
 * nCr = n-1Cr-1 + n-1Cr でメモ化再帰で求める
 * n=66 までならlong longでオーバーフローしないことが保証される
 *   - C(66,33) ≒ 7e18 （long long だとギリギリ収まる）
 */
template<typename T>
T combination_rec(T n, T r) {
    static vector c_memo(67, vector<T>(67, -1)); // 二項係数のメモ

    r = min(n-r, r);
    if (r < 0) return 0;
    if (c_memo[n][r] != -1) return c_memo[n][r];
    if (n == 0) return c_memo[n][r] = 1;
    if (r == 0) return c_memo[n][r] = 1;
    return c_memo[n][r] = combination_rec<T>(n-1, r-1) + combination_rec<T>(n-1, r);
}

// # n個の中からr個を取り出す順列の組み合わせ数は
// # nPr = n!/(n-r)!
// # 階乗部分を展開して割り算すれば、Π(n-r+1, n)なので、計算量はO(r-1)
template<typename T>
T permutation(T n, T r) {
    T ans = 1;
    for (T i=n; i>n-r; --i) {
        ans = ans*i;
    }
    return ans;
}

void solve() {
    string S; cin >> S;
    set<ll> oset;  // oの数字の集合
    set<ll> oqset; // oと?の数字の集合
    for(ll i=0; i<10; i++) {
        if (S[i] == 'o') {
            oset.insert(i);
            oqset.insert(i);
        }
        else if (S[i] == '?') {
            oqset.insert(i);
        }
    }

    // 実際に4けたの暗証番号を全探索で作り、ありえないものを除外する
    ll ans = 0;
    for(ll d0: oqset) {
        for(ll d1: oqset) {
            for(ll d2: oqset) {
                for(ll d3: oqset) {
                    // osetの数字はすべて使われているかチェックする
                    bool is_ok = true;
                    for(ll o_num: oset) {
                        if (d0==o_num || d1==o_num || d2==o_num || d3==o_num) continue;
                        is_ok = false;
                        break;
                    }

                    if (is_ok) ans++;
                }
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}