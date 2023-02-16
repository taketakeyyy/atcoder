#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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

/** 自動でMODをとるModInt型
 *
 * Usage
 *   // 基本的な使い方
 *   mint a, b;
 *   a = 100;
 *   b = a + MOD;
 *   // istreamとostreamをオーバロードしてるので、mint型も普通に入出力できる
 *   cout << b << endl;  // 100
 *   // 明示的にlong long型を出力するときは.xを参照する
 *   cout << b.x << endl;  // 100
 *
 * References
 *  https://youtu.be/L8grWxBlIZ4?t=9858
 *  https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
 *  https://youtu.be/8uowVvQ_-Mo?t=1329 : division
 */
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
    bool operator<=(const mint a) const { return mint(*this) <= a; }
    bool operator<(const mint a) const { return mint(*this) < a; }
    bool operator>=(const mint a) const { return mint(*this) >= a; }
    bool operator>(const mint a) const { return mint(*this) > a; }
    bool operator==(const mint a) const { return mint(*this) == a; }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

/*** BIT実装例
・N個の変数 v[1], ..., v[N]
    - すべて0で初期化
・2種類のクエリ
    - v[a]に値wを加える
    - prefix[1,a]のところの区間和v[1]+v[2]+..+v[a]を求める
・クエリあたりO(logN)時間にしたい

bit[1]からbit[N]までを使用(便宜上bit[0]は使用しない)
bit[1] := v[1]
bit[2] := v[1]+v[2]
bit[3] := v[3]
bit[4] := v[1]+v[2]+v[3]+v[4]
bit[5] := v[5]
***/
template <typename T>
class BIT {
    private:
        /* 引数チェック */
        void _check_args_add(size_t a) {
            if (a <= 0 || this->N < a) {
                try {
                    throw "Error BIT.add(a, w): Arg 'a' MUST '1 <= a <= N'.";
                }
                catch (const char *str) {
                    cerr << str << endl;
                    terminate();
                }
            }
        }

        /* 引数チェック */
        void _check_args_sum(size_t a) {
            if (a <= 0 || this->N < a) {
                try {
                    throw "Error BIT.add(a, w): Arg 'a' MUST '1 <= a <= N'.";
                }
                catch (const char *str) {
                    cerr << str << endl;
                    terminate();
                }
            }
        }

    public:
        size_t N;  // 要素数
        vector<T> bit;  // bit配列

        BIT(size_t n) {
            this->N = n;
            this->bit.resize(n+1, 0);
        }

        /**
         * @brief v[a]番目に値wを加える
         * @details O(logN)
         */
        void add(size_t a, T w) {
            // エラー処理
            _check_args_add(a);

            size_t x = a;
            while (x <= this->N) {
                this->bit[x] += w;
                x += x&-x;
            }
        }

        /**
         * @brief vの区間[1,a]の和を求める
         * @details O(logN)
         */
        T sum(size_t a) {
            _check_args_sum(a);

            T ret = 0; size_t x = a;
            while (x > 0) {
                ret += this->bit[x];
                x -= x&-x;
            }
            return ret;
        }
};



// 解説AC
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 座圧が必要なのでmapでやる
    map<ll,ll> a2idx; // key: A[i], value: BITのインデックス
    for(ll i=0; i<N; i++) a2idx[A[i]] = 0;

    // A[i]に対するBITのインデックスを埋めていく（座圧）
    ll m = 0; // BITのインデックス
    for(auto &p: a2idx) p.second = ++m;
    BIT<mint> bit(m);

    // 答えを求める
    mint ans = 0;
    mint pow2 = 1, ipow2 = 1; // 2のべき乗と、2のべき乗の逆元
    for(ll r=0; r<N; r++) {
        ll idx = a2idx[A[r]];
        ans += pow2 * bit.sum(idx);
        pow2 *= 2; ipow2 /= 2;
        bit.add(idx, ipow2);
    }
    cout << ans << endl;
}

// 解説AC
void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // A[i]の取りうる値は大きいのでBITのインデックスは座圧が必要
    map<ll,ll> bitidx; // key: A[i], value: BITのインデックス
    for(ll i=0; i<N; i++) bitidx[A[i]] = 0;
    {
        ll idx = 1; // BITのインデックス
        for(auto &[_, val]: bitidx) val = idx++;
    }

    // 答えを求める
    BIT<mint> bit(bitidx.size());
    mint ans = 0;
    mint pow2 = 2, ipow2 = mint(1)/2; // 2のべき乗と、2のべき乗の逆元
    bit.add(bitidx[A[0]], ipow2);
    for(ll r=1; r<N; r++) {
        ll idx = bitidx[A[r]];
        ans += pow2 * bit.sum(idx);
        pow2 *= 2; ipow2 /= 2;
        bit.add(idx, ipow2);
    }
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}