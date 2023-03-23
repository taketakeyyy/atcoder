#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

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
    ull N; cin >> N;
    ull n = cbrt(1e18) + 1;
    vector<ull> primes = sieve<ull>(n);
    // cout << primes[primes.size()-1] << endl;
    // cout << ULONG_LONG_MAX << endl;

    ull ans = 0;
    for(ull i=0; i<primes.size(); i++) {
        ull p = primes[i];
        if (p >= N) break;

        for(ull j=i+1; j<primes.size(); j++) {
            ull q = primes[j];
            // オーバーフロー注意
            ull a = q*q*q;
            if (a >= N) { break; }
            if (p > ULONG_LONG_MAX/a) { break; }
            a *= p;
            if (a <= N) {
                ans++;
            }
            else { break; }
        }
    }

    cout << ans << endl;
}

// 解説AC
// 尺取法
void solve2() {
    ll N; cin >> N;
    vector<ll> primes = sieve<ll>(1e6);

    // p*q*q*q <= N となる最大のqを探す
    ll ans = 0;
    ll l = 0; // pのインデックス
    ll p = primes[l];
    ll r = 0; // qのインデックス
    for(ll i=l+1; i<(ll)primes.size(); i++) {
        ll q = primes[i];
        double k = p*q*q*q; // double型は 1.7e308 まで表現可能!!!
        if (k <= N) {
            r = i;
            continue;
        }
        break;
    }
    ans += r - l;

    // pを素数1個分大きくすると、qはかならず減少するので、尺取法が使える
    while(r-l > 0) {
        l++;
        ll p = primes[l];
        while(r-l > 0) {
            ll q = primes[r];
            double k = p*q*q*q;
            if (k <= N) {
                ans += r - l;
                break;
            }
            r--;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    // solve2();
    return 0;
}