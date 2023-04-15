#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define intceil(a, b) ((a + (b - 1)) / b)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long, long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x, y); }
void chmin(int& x, int y) { x = min(x, y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = {-1, 0, 1, 0};
vector<ll> vx = {0, 1, 0, -1};
#include <atcoder/modint>
using namespace atcoder;
// using mint = modint998244353;

// /** 自動でMODをとるModInt型
//  *
//  * Usage
//  *   // 基本的な使い方
//  *   mint a, b;
//  *   a = 100;
//  *   b = a + MOD;
//  *   // istreamとostreamをオーバロードしてるので、mint型も普通に入出力できる
//  *   cout << b << endl;  // 100
//  *   // 明示的にlong long型を出力するときは.xを参照する
//  *   cout << b.x << endl;  // 100
//  *
//  * References
//  *  https://youtu.be/L8grWxBlIZ4?t=9858
//  *  https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
//  *  https://youtu.be/8uowVvQ_-Mo?t=1329 : division
//  */
struct mint {
    ll x;  // typedef long long ll;
    mint(ll x = 0) : x((x % MOD + MOD) % MOD) {}
    mint operator-() const { return mint(-x); }
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD - a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) {
        (x *= a.x) %= MOD;
        return *this;
    }
    mint operator+(const mint a) const { return mint(*this) += a; }
    mint operator-(const mint a) const { return mint(*this) -= a; }
    mint operator*(const mint a) const { return mint(*this) *= a; }
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t >> 1);
        a *= a;
        if (t & 1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD - 2); }
    mint& operator/=(const mint a) { return *this *= a.inv(); }
    mint operator/(const mint a) const { return mint(*this) /= a; }
    bool operator<=(const mint a) const { return mint(*this) <= a; }
    bool operator<(const mint a) const { return mint(*this) < a; }
    bool operator>=(const mint a) const { return mint(*this) >= a; }
    bool operator>(const mint a) const { return mint(*this) > a; }
    bool operator==(const mint a) const { return mint(*this) == a; }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x; }
ostream& operator<<(ostream& os, const mint& a) { return os << a.x; }

void solve() {
    ll Q;
    cin >> Q;

    deque<ll> S;
    S.push_back(1);
    mint ans = 1;
    mint pow10 = 1;  // 最上位の桁
    for (ll q = 0; q < Q; q++) {
        ll query;
        cin >> query;
        if (query == 1) {
            // S の末尾に数字 x を追加する
            ll x;
            cin >> x;
            S.push_back(x);
            ans *= 10;
            ans += mint(x);
            pow10 *= 10;
        } else if (query == 2) {
            // S の先頭の数字を削除する
            mint x = S.front();
            S.pop_front();
            ans -= x * pow10;
            pow10 /= 10;
        } else {
            // 出力する
            cout << ans << endl;
        }
    }
}

// 解説AC
// ACL 使用
// void solve2() {
//     ll Q;
//     cin >> Q;

//     deque<ll> S;
//     S.push_back(1);
//     mint ans = 1;

//     for (ll q = 0; q < Q; q++) {
//         ll t;
//         cin >> t;
//         if (t == 1) {
//             ll x;
//             cin >> x;
//             S.push_back(x);
//             ans = ans * 10 + x;
//         } else if (t == 2) {
//             ans -= mint(10).pow(S.size() - 1) * S.front();  // 繰り返し二乗法
//             S.pop_front();
//         } else {
//             cout << ans.val() << endl;
//         }
//     }
// }

int main() {
    solve();
    // solve2();
    return 0;
}