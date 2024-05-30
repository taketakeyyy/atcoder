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

// 素数を小さい方から順に掛け算していく。
// 2 × 3 × 5 × 7 × 11 × 13 = 30030
// 2 × 3 × 5 × 7 × 11 × 13 × 17 = 510510 (これで10^5を超える)
// よって、10^5以下の数を素因数分解したときの、素因数の個数は最大で6個
void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // Aが、なんの素因数の掛け合わせで割り切れるか個数を数える
    map<ll,ll> cnt; // cnt[mul] := mulで割り切れるAの個数
    for(ll i=0; i<N; i++) {
        // 10^5以下の数を素因数分解したときの、素因数の数はとても少ない（6個程度）
        auto pfMap = prime_factor_ver_map<ll>(A[i]);
        vector<ll> primes;
        for(auto[key, val]: pfMap) primes.push_back(key);
        ll PN = primes.size();

        for(ll bit=1; bit<(1<<PN); bit++) {
            ll mul = 1; // 素因数の掛け合わせ
            for(ll d=0; d<PN; d++) {
                if (bit>>d&1) mul *= primes[d];
            }
            cnt[mul]++;
        }
    }

    // 各mについて答えを求める
    for(ll m=1; m<=M; m++) {
        // mの素因数を求める
        auto pfMap = prime_factor_ver_map<ll>(m);
        vector<ll> primes;
        for(auto[key, val]: pfMap) primes.push_back(key);
        ll PN = primes.size();

        // n(p) := mの素因数pと割り切れるものの個数
        // n(p0 ∪ p1 ∪ p2 ∪ ...)を包除原理で求める
        ll notAns = 0;
        for(ll bit=0; bit<(1<<PN); bit++) {
            // ビットが立っている素因数をqとする。n(q0 ∩ q1 ∩ ...)を求める（q0かつq1かつ...で割り切れるものの個数）
            ll popcnt = __builtin_popcountll(bit);
            ll mul = 1; // 素因数qの掛け合わせ
            for(ll d=0; d<PN; d++) {
                if (bit>>d&1) {
                    mul *= primes[d];
                }
            }
            // 包除原理の積集合の足し引き計算
            if (popcnt%2 == 0) notAns -= cnt[mul];
            else notAns += cnt[mul];
        }
        // 答えは余事象
        ll ans = N - notAns;
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}