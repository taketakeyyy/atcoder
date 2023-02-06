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
    static vector c_memo(67, vector<ll>(67, -1)); // 二項係数のメモ

    r = min(n-r, r);
    if (r < 0) return 0;
    if (c_memo[n][r] != -1) return c_memo[n][r];
    if (n == 0) return c_memo[n][r] = 1;
    if (r == 0) return c_memo[n][r] = 1;
    return c_memo[n][r] = combination_rec<T>(n-1, r-1) + combination_rec<T>(n-1, r);
}


// 解説AC
// 「辞書順が関係する問題では、前の文字から決めていくというのが定石です」
//
// (例) A=2, B=2, K=4の場合を考える。
// [ステップ1]
// aが先頭に来る場合、axxxの形をした文字列は、残りaが1個、bが2個なので、C(3,1) = 3通り。
// よって、axxxの形をした文字列は1~3番目の文字列が入っているので、K=4番目の文字列はbxxxの形をしている。
// なので、1文字目はbで確定。
// [ステップ2]
// 残りの3文字について、aが先頭に来る場合、baxxの形をした文字列は、残りaが1個、bが1個なので、C(2,1) = 2通り。
// よって、baxxの形をした文字列は4~5番目の文字列が入っているので、K=4番目の文字列はbaxxの形をしている。
// なので、2文字目はaで確定。
// [ステップ3]
// ...というのを、再帰的に決めていけば、K番目の文字列が求まる。
void solve() {
    ll A, B, K; cin >> A >> B >> K;

    string ans;
    while(A+B > 0) {
        if (A == 0) {
            ans += {'b'};
            B--;
        }
        else if (B == 0) {
            ans += {'a'};
            A--;
        }
        else {
            ll c = combination_rec<ll>(A+B-1, A-1);
            if (K <= c) {
                ans += {'a'};
                A--;
            }
            else {
                ans += {'b'};
                B--;
                K -= c;
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}