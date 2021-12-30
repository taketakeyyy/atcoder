#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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
    a %= m;
    T res = mod_pow<T>(a*a, n/2, m);
    if (n&1) res = (res * a) % m;
    return res;
}

void __solve() {
    // 以下を試せばわかるが、累乗の指数部をMODとったら答えが変わる
    ll ans1 = mod_pow<ll>(2, MOD+1, MOD);
    ll ans2 = mod_pow<ll>(2, (MOD+1)%MOD, MOD);
    cout << ans1 << " " << ans2 << endl;
}

void solve() {
    // AC
    ll N, K, M; cin >> N >> K >> M;
    M %= MOD;
    if (M==0) {  // pow(0,0)=1になっちゃうので
        cout << 0 << endl;
    }
    else {
        ll c = mod_pow<ll>(K, N, MOD-1);  // 指数部のNは MOD したら駄目なので、そうならないように注意（基数はOK）
        ll ans = mod_pow<ll>(M, c, MOD);
        cout << ans << endl;
    }
}

void solve2() {
    // 駄目解法。
    ll N, K, M; cin >> N >> K >> M;
    M %= MOD;
    if (M==0) {  // pow(0,0)=1になっちゃうので
        cout << 0 << endl;
    }
    else {
        ll c = mod_pow<ll>(K, N%(MOD-2), MOD-1); // これだめ。MOD-1は素数じゃないのでフェルマーの小定理が成り立たない
        ll ans = mod_pow<ll>(M, c, MOD);
        cout << ans << endl;
    }
}

void solve3() {
    ll N, K, M; cin >> N >> K >> M;
    M %= MOD;
    if (M==0) {  // pow(0,0)=1になっちゃうので
        cout << 0 << endl;
    }
    else {
        ll c = mod_pow<ll>(K, N%(MOD-1), MOD-1);  // 指数部を MOD したら駄目
        ll ans = mod_pow<ll>(M, c, MOD);
        cout << ans << endl;
    }
}

int main() {
    solve();
    return 0;
}