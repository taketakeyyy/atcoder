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

/*
正整数nを素因数分解して、因数をkey、指数部をvalueとしたmapを返す関数
*/
template <typename T>
map<T, T> prime_factor_ver_map(T n) {
    map<T, T> ans;
    if (n <= 1) return ans;

    for (T i=2; i*i<=n; i++) {
        while (n%i == 0) {
            ans[i]++;
            n /= i;
        }
    }

    if (n != 1) ans[n]++;

    return ans;
}

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
    auto primes = sieve(sqrt(N/12+1)+1);
    sort(primes.begin(), primes.end());

    ll ans = 0;
    for(ll i=0; i<(ll)primes.size(); i++) {
        ll a = primes[i];
        if (a*a >= N) break;
        for(ll j=i+1; j<(ll)primes.size(); j++) {
            ll b = primes[j];
            if (a*a*b >= N) break;

            // cは二分探索で求める
            ll c = sqrt(N/(a*a*b)); // 誤差気になるが...
            ll k = upper_bound(primes.begin(), primes.end(), c) - primes.begin() - 1;
            if (k <= j) break;
            ans += (k-j);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}