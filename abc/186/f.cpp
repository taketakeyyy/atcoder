#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
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


long long euler_phi(long long n) {
    /***
     * オイラー関数Φ(n)を求める
     * 計算量はO(√n)
     ***/
    long long res = n;
    for (long long i=2; i*i<=n; i++) {
        if (n%i==0) {
            res = res / i * (i-1);
            for (; n%i==0; n/=i);
        }
    }
    if (n!=1) res = res / n * (n-1);
    return res;
}


long long mod_pow(long long a, long long n, long long m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    long long res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}


void solve(){
    /**
     * Kx + S = 0 (mod N) となる最小のxを求める
     * Kx = -S (mod N)
     * x = -S/K
     * */
    int T; cin >> T;
    for (int i=0; i<T; i++){
        long long N, S, K; cin >> N >> S >> K;

        // なぜgで割る？
        // N=8, S=2, K=6のとき、gcd(N,K)!=1なので-1なのか？
        // 実はそうではなくて、x=1で玉座に座れる。
        // おのおのg=2で割ると、
        // N=4, S=1, K=3
        // となり、計算することが可能…なのだが、やっぱりなぜgで割る必要があるのかイマイチわからん
        int g = gcd(gcd(N, K), S);
        N=N/g; K=K/g; S=S/g;

        if (gcd(N,K)!=1) {
            cout << -1 << endl;
            continue;
        }
        // x = -S/Kを計算する
        long long x = ((-S+N)*mod_pow(K, euler_phi(N)-1LL, N))%N;
        cout << x << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}