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
template <typename T>
vector<T> sieve(T n) {
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

// N = p^2 * q
// Nは与えられる。
// pが決まればqは自動的に決まる
void solve() {
    ll T; cin >> T;
    // auto primes = sieve(3000000000);

    for(ll t=0; t<T; t++) {
        ll N; cin >> N;
        // 素因数分解
        ll p, q;
        ll dcnt = 0;  // 割れた回数

        // 2で割れるかチェック
        while (N%2 == 0) {
            dcnt++;
            N /= 2;
        }
        if (dcnt != 0) {
            if (dcnt == 2) {
                p = 2;
                q = N;
            }
            else {
                q = 2;
                p = sqrt<ll>(N);  // これ大丈夫？
            }
            cout << p << " " << q << endl;
            continue;
        }

        // 3以降
        for (ll i=3; i*i<=N; i+=2) {
        // for(ll i: primes) {
            while (N%i == 0) {
                dcnt++;
                N /= i;
            }
            if (dcnt != 0) {
                if (dcnt == 2) {
                    p = i;
                    q = N;
                }
                else {
                    q = i;
                    p = sqrt<ll>(N);  // これ大丈夫？
                }
                break;
            }
        }
        cout << p << " " << q << endl;
    }
}


// エラトステネスの篩で、N以下の素数の配列を返す
vector<ll> sieve(ll n) {
    vector<ll> primes;
    vector<bool> is_prime(n+1, true);
    for(ll i=2; i<=n; i++) {
        if(!is_prime[i]) continue;

        primes.push_back(i);
        for(ll j=2*i; j<=n; j+=i) {
            is_prime[j] = false;
        }
    }
    return primes;
}

// 解説AC
// N <= 9 * 10^{18} なので、N以下の素数を求めるためにエラトステネスの篩をしようとするとTLEする。
// N = p^2 * q ということは、pとqの少なくとも一方はNの三乗根以下である。
// ※ pとqの両方がNの三乗根以上だと、Nより大きくなってしまうことからも自明。
// なので、Nの三乗根以下までの素数を調べればOK。
void solve2() {
    ll T; cin >> T;
    for(ll t=0; t<T; t++) {
        ll N; cin >> N;

        // Nの三乗根を求める
        ll cbrt3N;
        for(ll i=1; i*i*i<=N; i++) cbrt3N = i;
        cbrt3N += 1;  // 念のため少し多めに確保

        // Nの三乗根以下の素数の配列を得る
        auto primes = sieve(cbrt3N);

        // Nが素数で割り切れるなら、pとqは確定できる
        ll p, q;
        for(ll pm: primes) {
            if (N%(pm*pm) == 0) {
                p = pm;
                q = N/(p*p);
                break;
            }
            if (N%pm == 0) {
                q = pm;
                p = sqrt<ll>(N/q);
                break;
            }
        }

        cout << p << " " << q << endl;
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}