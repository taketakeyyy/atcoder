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
  mint inv() const {
    return pow(MOD-2);
  }
  mint& operator/=(const mint a) { return *this *= a.inv();}
  mint operator/(const mint a) const { return mint(*this) /= a;}
};


map<ll,ll> inv_memo;
ll inv(ll x) {
    if (inv_memo.count(x)) return inv_memo[x];
    inv_memo[x] = mint(x).inv().x;
    return inv_memo[x];
}

vector<ll> primes;  // 素数
vector<ll> divided; // エラトステネスで篩をかけられたときに割られた数

map<ll,ll> prime_factor(ll a) {
    // aを素因数分解して返す
    map<ll,ll> res;
    while(1) {
        ll d = divided[a];
        if (d==-1) {
            res[a]++;
            break;
        }
        res[d]++;
        a /= d;
    }
    return res;
}

void lcm_prime_factor(map<ll,ll> &mpa, map<ll,ll> mpb) {
    // aとbのLCMの結果を、素因数分解で保持する
    for(auto [p, q]: mpb) {
        mpa[p] = max(mpa[p], mpb[p]);
    }
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];
    if (N==1) {
        cout << 1 << endl;
        return;
    }

    // 素数を作っておく
    const ll PMAX = 1000000;
    divided.resize(PMAX+1, -1);
    vector<bool>is_primes(PMAX+1, true);
    is_primes[0] = false; is_primes[1] = false;
    for(ll i=2; i<=PMAX; i++) {
        if (is_primes[i]) {
            primes.push_back(i);
            for(ll j=i*i; j<=PMAX; j+=i) {  // j=i*iはじまりにするとよい（j=i*(i-1)以下は、i=(i-1)以下のときの篩で消してるので）
                is_primes[j] = false;
                divided[j] = i;
            }
        }
    }

    vector<ll> B0s(N-1);
    vector<ll> B(N);
    for(ll i=1; i<N; i++) {
        ll g = gcd(A[0], A[i]);
        ll b0, bj;
        bj = A[0]/g;
        b0 = A[i]/g;
        B0s[i-1] = b0;
        B[i] = bj;
    }

    // B[0]はB0sのlcm
    // lcmはMODを取ってはダメで、非常に大きくなる可能性がある
    // lcm(a,b)とは、aとbの素因数分解したときのp^qaとp^qbの各素因数pについてp^(max(qa,qb))とすることである。
    // 素因数分解で保持することで、クソデカ整数をなんとか保持できる
    map<ll,ll> mplm = prime_factor(B0s[0]);
    for (ll i=0; i<N-1; i++) {
        lcm_prime_factor(mplm, prime_factor(B0s[i]));
    }

    // B[0]を決める
    B[0] = 1;
    for(auto [p,q]: mplm) {
        for(ll i=0; i<q; i++) {
            B[0] *= p;
            B[0] %= MOD;
        }
    }

    // B[i]が決まっていく
    for (ll i=1; i<N; i++) {
        // B[i] *= B[0]/B0s[i-1]; // MODの世界の割り算は、逆元をかけないといけない
        B[i] *= (B[0] * inv(B0s[i-1])) % MOD;
        B[i] %= MOD;
    }

    // 出力
    ll ans = 0;
    for (ll i=0; i<N; i++) {
        ans += B[i];
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}