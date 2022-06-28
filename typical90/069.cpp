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

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}


void solve() {
    ll N, K; cin >> N >> K;

    // コーナーケース
    if (N == 1) {
        cout << K << endl;
        return;
    }
    if (N == 2) {
        if (K == 1) {
            cout << 0 << endl;
        }
        else {
            cout << K*(K-1) << endl;
        }
        return;
    }
    if (K <= 2) {
        cout << 0 << endl;
        return;
    }

    // K * (K-1) * (K-2) * (K-2) *...
    ll ans = K * (K-1);
    ans %= MOD;
    ans *= mod_pow<ll>(K-2, N-2, MOD);
    ans %= MOD;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}