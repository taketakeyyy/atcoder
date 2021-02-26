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


void solve(){
    ll N, K; cin >> N >> K;

    vector<ll> As(N);
    ll mxA = -1;
    rep(i,N) {
        cin >> As[i];
        mxA = max(mxA, As[i]);
        if (As[i]==K) {
            cout << "POSSIBLE" << endl;
            return;
        }
    }

    if (mxA < K) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    // Asの中で一番大きい値をmax(As)とする
    // max(As)からうまいこと引いてKにしたい。
    // Asの任意の2つのボールの最大公約数が、作れるボールである。
    // Asを順番に最大公約数をとっていき、最終的な最大公約数をgとする
    // K - max(As) がgで割り切れたら、POSSIBLEである。
    ll g = As[0];
    for (int i=1; i<N; i++) {
        g = gcd(g, As[i]);
    }

    if ((K-mxA)%g==0) {
        cout << "POSSIBLE" << endl;
        return;
    }
    cout << "IMPOSSIBLE" << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}