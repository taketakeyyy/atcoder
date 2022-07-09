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
map<T,T> lcm_prime_factor(const map<T,T> &mpa, const map<T,T> &mpb) {
    /* 最小公倍数lcm(a,b)の結果を、素因数分解で保持する
     * Args:
     *   mpa: aの素因数分解
     *   mpb: bの素因数分解
     */
    map<T,T> res;
    for(auto [p, q]: mpb) {
        res[p] = max(mpa.at(p), mpb.at(p));
    }
    return res;
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
    vector<map<ll,ll>> A(N);  // A[i] := A[i]の値を素因数分解で保持

    // A[i]全体の最小公倍数をLCMとする。LCMは各素因数の肩がmaxのものをかけたもの。
    // 素因数の肩で単独maxを持つものを数える
    // 単独maxを持つものを1に変えたとき、LCMに変化が起こるので、その数を数えればよい
    // 1に変えてもLCMに変化がないやつがあるかどうかで答えに＋１するかが決まるので、それに注意
    map<ll,ll> maxp;
    for(ll i=0; i<N; i++) {
        ll M; cin >> M;
        for(ll m=0; m<M; m++) {
            ll p, e; cin >> p >> e;
            A[i][p] = e;

            if (e > maxp[p]) { maxp[p] = e; }
        }
    }

    // LCMを作る
    map<ll,ll> LCM;
    for(ll i=0; i<N; i++) {
        for(auto[p, e] : A[i]) {
            LCM[p] = max(LCM[p], e);
        }
    }

    map<ll,ll> cnt;  // LCMと同じ肩をもつものの数
    for(ll i=0; i<N; i++) {
        for(auto[p, e]: A[i]) {
            if (LCM[p] == e) { cnt[p]++; }
        }
    }

    // 単独maxを持つものを数える
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        bool is_ok = false;
        for(auto[p, e]: A[i]) {
            if (LCM[p]==e && cnt[p]==1) { is_ok = true; break; }
        }
        if (is_ok) ans++;
    }

    // ans < N なら、単独maxを1つも持たないものが存在する
    // そいつは1に変えてもLCMに影響しない(その場合はLCM自身も答えに含まれる)
    if (ans < N) { ans++; }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}