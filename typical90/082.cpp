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

ull keta(ull x) {
    // 桁数を返す
    if (x <= 9) return 1;
    ull res = 0;
    while(x != 0) {
        x /= 10;
        res++;
    }
    return res;
}

ull tousa(ull a, ull l) {
    // 等差数列の和。初項a, 末項l
    ull n = (l - a) + 1;
    // return (n%MOD) * ((a + l)%MOD) / 2;  // 2で割るな逆元をかけろ
    ull res = ((n%MOD) * (((a%MOD) + (l%MOD))%MOD)) % MOD;
    return (res * mod_pow<ull>(2, MOD-2, MOD)) % MOD;  // 2^{-1} = 2^{p-2}
}


void solve() {
    ull L, R; cin >> L >> R;

    // E[i] := i桁の文字は何個？
    vector<ull> E(20);
    ull now = L;
    while(1) {
        ull nketa = keta(now);
        ull big = 1;
        for(ull i=0; i<nketa; i++) big *= 10;

        if (R >= big) {
            E[nketa] = tousa(now, big-1)%MOD;
            now = big;
            continue;
        }
        else {
            E[nketa] = tousa(now, R)%MOD;
            break;
        }
    }

    // 最終的な文字の個数は？
    ull ans = 0;
    for(ull i=0; i<20; i++) {
        ans += (E[i]*i)%MOD;
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}