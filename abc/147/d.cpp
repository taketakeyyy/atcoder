#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

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


void solve(){
    // 普通にO(N^2)で解こうとしても間に合わない
    // XOR演算は各桁について独立であることに注目する
    // bを整数を2進数で表したときのb桁目とする
    // (A1 xor A2) + (A1 xor A3) + (A1 xor A4) + ...
    // の、(Ai xor Aj)の部分をXに置き換えて、
    // X1 + X2 + X3 + ...
    // とする。(Xのk番目の要素をXkとする)
    // 「Xkのd桁目が1であるもの」の個数をNdとする
    // 求める答え = Σ_{d=0~59} (Nd * 2^d)　となる。

    // というわけで、各Ndを求めたい。
    // Xk = (Ai xor Aj) より、
    // 「Xkのd桁目が1になる」には、
    // (1) 「Aiのd桁目が1」かつ「Ajのd桁目が0」
    // (2) 「Aiのd桁目が0」かつ「Ajのd桁目が1」
    // 上の2パターンである。
    // 上記の2パターンの個数 = (Aiのd桁目が1の個数)*(Aiのd桁目が0の個数)で求まる。

    ll N; cin >> N;
    vector<ll> As(N);
    rep(i,N) cin >> As[i];

    ll ans = 0;
    for (int d=0; d<60; d++) {
        ll x = 0;  // Aiのd桁目が1の個数
        for(int i=0; i<N; i++) {
            if (As[i]>>d&1) {
                x++;
            }
        }
        ll Nd = (x * (N-x)) % MOD;  // 「Xkのd桁目が1になる」個数
        ans += (Nd * mod_pow<ll>(2,d,MOD))%MOD;
        ans %= MOD;
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}