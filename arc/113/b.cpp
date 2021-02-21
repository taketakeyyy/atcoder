#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
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
    map<ll,ll>mods;
    // mods[0] = 1;
    mods[1] = 1;
    mods[2] = 4;
    mods[3] = 4;
    mods[4] = 2;
    mods[5] = 1;
    mods[6] = 1;
    mods[7] = 4;
    mods[8] = 4;
    mods[9] = 2;

    map<ll, vector<ll>>table;
    table[2] = {6,2,4,8};
    table[3] = {1,3,9,7};
    table[4] = {6,4};
    table[5] = {5};
    table[6] = {6};
    table[7] = {1,7,9,3};
    table[8] = {6,8,4,2};
    table[9] = {1,9};


    ll A, B, C; cin >> A >> B >> C;
    if (A%10LL==0LL) {
        cout << 0 << endl;
        return;
    }
    else if (A%10LL==1LL) {
        cout << 1 << endl;
        return;
    }
    ll BC = mod_pow<ll>(B,C,mods[A%10]);
    cout << table[A%10][BC] << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}