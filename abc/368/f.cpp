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


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // B[i] := A[i]の重複を許す素因数の個数
    vector<ll> B(N);
    for(ll i=0; i<N; i++) {
        auto mp = hspf.query(A[i]);
        for(auto[key, val]: mp) B[i] += val;
    }

    // ニム和を求める
    ll nim = 0;
    for(ll i=0; i<N; i++) {
        nim ^= B[i];
    }
    if (nim == 0) cout << "Bruno" << endl;
    else cout << "Anna" << endl;
}


int main() {
    solve();
    return 0;
}