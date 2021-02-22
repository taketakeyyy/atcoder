#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 998244353
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
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
    ll N, M, K; cin >> N >> M >> K;

    if (N==1 && M>=1) {
        cout << mod_pow<ll>(K,M,MOD) << endl;
        return;
    }
    if (M==1 && N>=1) {
        cout << mod_pow<ll>(K,N,MOD) << endl;
        return;
    }

    // N,M>=2のとき
    // max(A) <= min(B) が成り立つ（問題の重要な性質）

    // (1) max(A) = 1のとき
    // Aの並び方・・・全て1のみの1通り
    // Bの並び方・・・1~KのK^M通り

    // (2) max(A) = 2のとき
    // Aの並び方・・・1~2のみの2^N通り
    // Bの並び方・・・2~Kの(K-2+1)^M通り

    // (3) max(A) = xのとき
    // Aの並び方・・・1~xのみのx^N通り
    // Bの並び方・・・x~Kの(K-x+1)^M通り
    mint ans = mint(0);
    for (ll x=1; x<=K; x++) {
        ll a = mod_pow<ll>(x,N,MOD) - mod_pow<ll>(x-1,N,MOD);  // 重複分を引く
        ll b = mod_pow<ll>(K-x+1,M,MOD);
        ans += (a*b)%MOD;
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}