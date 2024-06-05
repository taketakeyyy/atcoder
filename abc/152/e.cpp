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

/**
 * @brief 高速素因数分解
 * 前計算でエラトステネスの篩を行うことで、1~Nまでの素因数分解を高速化する
 * 何度も素因数分解をするときに有用。
 * 構築：O(NloglogN)
 * クエリ：O(logN)
 *
 * @example
 * // 1~Nまでの素因数分解を高速化する
 * ll N = 1e6;
 * HighSpeedPrimeFactor hspf(N);
 * // 36を素因数分解
 * map<ll,ll> pf = hspf.query(36);
 *
 */
class HighSpeedPrimeFactor {
private:
    ll mN; // 1~Nまでの素因数分解を高速化する
    vector<ll> m_divided; // m_divided[x] := xは何の素数で割れたか

public:
    /**
     * @brief 1~N以下の高速素因数分解を構築する
     * 計算量O(NloglogN)
     * @param N
     */
    HighSpeedPrimeFactor(ll N): mN(N) {
        // エラトステネスの篩を行う
        vector<ll> primes; // 素数を格納
        vector<bool> is_prime(N+1, true); // 素数かどうか
        is_prime[0] = is_prime[1] = false;
        m_divided.assign(N+1, -1);
        for(ll i=2; i<=N; i++) {
            if (!is_prime[i]) continue;
            primes.push_back(i);

            // iの倍数を篩い落とす
            for(ll j=i*i; j<=N; j+=i) { // j=i*iはじまりでOK. なぜならi*(i-1)以下は、i=(i-1)以下のときの篩で消えているから
                is_prime[j] = false;
                m_divided[j] = i;
            }
        }
    }

    /**
     * @brief xを素因数分解する
     * 計算量 O(logN)
     * @param x
     * @return map<ll,ll> 素因数分解の結果 key:素因数, val:素因数の個数
     */
    map<ll,ll> query(ll x) {
        map<ll,ll> res; // key:素因数, val:素因数の個数
        while(x != 1LL) {
            ll d = m_divided[x];
            if (d==-1) {
                res[x]++;
                break;
            }
            res[d]++;
            x /= d;
        }
        return res;
    }
};
HighSpeedPrimeFactor hspf(1e6);


/**
 * @brief 最小公倍数lcm(res,a)の結果を、素因数分解で保持する
 * 引数resに対して破壊的操作をするので注意
 *
 * @tparam T
 * @param res resの素因数分解
 * @param mpa aの素因数分解
 */
template <typename T>
void lcm_prime_factor(map<T,T> &res, const map<T,T> &mpa) {
    for(auto [p, _]: mpa) {
        if (res.contains(p)) res[p] = max(res.at(p), mpa.at(p));
        else res[p] = mpa.at(p);
    }
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

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 各Aを素因数分解する
    vector<map<ll,ll>> prime_factors(N);
    for(ll i=0; i<N; i++) {
        prime_factors[i] = hspf.query(A[i]);
    }

    // LCM = lcm(A[0], A[1], ..., A[N-1]) を求める
    auto lcm_pf = prime_factors[0]; // LCM
    for(ll i=1; i<N; i++) {
        lcm_prime_factor(lcm_pf, prime_factors[i]);
    }

    // LCMを作る
    mint LCM = 1;
    for(auto[key, val]: lcm_pf) {
        LCM *= mod_pow<ll>(key, val, MOD);
    }

    // 答え
    mint ans = 0;
    for(ll i=0; i<N; i++) {
        ans += LCM * mint(A[i]).inv();
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}