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

template <typename T>
set<T> sieve(T n) {
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

    set<T> primes;  // 素数を格納する
    for (T i=2; i<n+1; i++) {
        if (is_prime[i]) {
            primes.insert(i);
            for (T j=i*i; j<n+1; j+=i) {  // j=i*iはじまりでOK. なぜならi*(i-1)以下は、i=(i-1)以下のときの篩で消えているから
                is_prime[j] = false;
            }
        }
    }
    return primes;
}


void solve() {
    ll A, B, C, D; cin >> A >> B >> C >> D;

    set<ll> primes = sieve<ll>(200);
    for (ll a=A; a<=B; a++) {
        bool takahashi = true;
        for (ll c=C; c<=D; c++) {
            if (primes.count(a+c)) {
                // a+cが素数だったとき、aを選んだら高橋は負ける
                takahashi = false;
                break;
            }
        }

        if (takahashi) {
            cout << "Takahashi" << endl;
            return;
        }
    }

    cout << "Aoki" << endl;
}


int main() {
    solve();
    return 0;
}