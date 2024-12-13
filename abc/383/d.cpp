#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


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
// HighSpeedPrimeFactor hspf(2e6+1);

template <typename T>
vector<T> sieve(T n) {
    /***
     * エラトステネスの篩
     *
     * Descriptions:
     *  n以下の素数を格納したのvectorを返す
     *  計算量はO(n log(log n))
     *
     * Args:
     *  n(T): 正整数
     *
     * Return:
     *  primes: 素数を格納したvector
     *
     ***/
    vector<bool> is_prime(n+1, true);  // is_prime[i] := 整数iは素数かどうか
    is_prime[0] = false; is_prime[1] = false;

    vector<T> primes;  // 素数を格納する
    for (T i=2; i<n+1; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (T j=i*i; j<n+1; j+=i) {  // j=i*iはじまりでOK. なぜならi*(i-1)以下は、i=(i-1)以下のときの篩で消えているから
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

void solve() {
    ll N; cin >> N;

    auto primes = sieve(2e6+1);
    ll PN = primes.size();

    unordered_set<ll> ansSet;
    for(ll i=0; i<PN; i++) {
        ll p1 = primes[i];
        ll num = p1*p1;
        if (num >= 2e6+1) {
            break;
        }
        for(ll j=i+1; j<PN; j++) {
            ll p2 = primes[j];
            num *= (p2*p2); // ????
            ll num2 = p1*p1*p2*p2;
            ll tmp = 0;
            if (num2 <= N) {
                ansSet.insert(num2);
            }
            else {
                break;
            }
        }
    }

    for(ll i=0; i<PN; i++) {
        ll p = primes[i];
        ll num = p*p*p*p*p*p*p*p;
        if (num <= N) {
            ansSet.insert(num);
        }
        else {
            break;
        }
    }

    cout << ansSet.size() << endl;
}


int main() {
    solve();
    return 0;
}