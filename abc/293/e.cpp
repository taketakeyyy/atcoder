#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
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
 * @brief 行列Aと行列Bのドット内積を計算する
 * 行列計算 AB を計算する
 *
 * @tparam T
 * @param A 行列
 * @param B 行列
 * @param mod
 * @return vector<vector<T>>
 */
template<typename T>
vector<vector<T>> mat_mul(vector<vector<T>> const &A, vector<vector<T>> const &B, T mod) {
    T rowA = A.size(); // 行数
    T colA = A[0].size(); // 列数
    T rowB = B.size(); // 行数
    T colB = B[0].size(); // 列数
    if (colA != rowB) throw runtime_error("cannot mat_mul.");

    vector<vector<T>> res(rowA, vector<T>(colB));
    for(size_t i=0; i<(size_t)rowA; i++) {
        for(size_t j=0; j<(size_t)colB; j++) {
            for(size_t k=0; k<(size_t)colA; k++) {
                res[i][j] += A[i][k]*B[k][j];
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

/**
 * @brief 行列累乗
 * 行列Aをn乗する。
 *
 * @tparam T
 * @param A 行列
 * @param n n乗する
 * @param mod
 * @return vector<vector<T>>
 */
template <typename T>
vector<vector<T>> mat_pow(vector<vector<T>> A, T n, T mod) {
    size_t row = A.size();
    size_t col = A[0].size();
    if (row != col) throw runtime_error("cannot mat_pow.");

    vector<vector<T>> res(row, vector<T>(col));
    for(size_t i=0; i<row; i++) res[i][i] = 1; // 単位行列

    while(n > 0) {
        if (n&1) res = mat_mul(res, A, mod);
        A = mat_mul(A, A, mod);
        n >>= 1;
    }
    return res;
}

// 解説AC
// 行列累乗
void solve() {
    ll A, X, M; cin >> A >> X >> M;
    vector mat(2, vector<ll>(2));
    mat[0][0] = A; mat[0][1] = 1;
    mat[1][0] = 0; mat[1][1] = 1;
    auto mat2 = mat_pow(mat, X, M);
    cout << mat2[0][1] << endl;
}

// 解説AC
// 割り算を使わない方法
void solve2() {
    ll A, X, M; cin >> A >> X >> M;

    // (A^0+...+A^{x-1}, A^x)を返す
    auto f = [&](auto f, ll x) -> pair<ll,ll> {
        if (x == 0) return {0,1};
        auto [total, p] = f(f, x/2);
        total += total*p; total %= M;
        p *= p; p %= M;
        if (x%2 == 1) {
            total = total*A+1; total %= M;
            p *= A; p %= M;
        }
        return {total, p};
    };

    ll ans = f(f,X).first;
    cout << ans << endl;
}

/**
 * @brief a^{n} mod m の計算を、繰り返し二乗法で求める
 * 計算量：O(log n)
 **/
template<typename T>
T mod_pow(T a, T n, T m) {
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

// 解説AC
// Mと互いに素とは限らないKで除算したい場合、mod MKで計算する
void solve3() {
    ll A, X, M; cin >> A >> X >> M;
    if (A == 1) {
        cout << X%M << endl;
    }
    else {
        ll bunsi = mod_pow(A,X,M*(A-1))-1;
        ll bunbo = (A-1)%M;
        ll ans = bunsi/bunbo;
        cout << ans << endl;
    }
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}