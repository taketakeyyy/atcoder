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


/** 自動でMODをとるModInt型
 *
 * Usage
 *   // 基本的な使い方
 *   mint a, b;
 *   a = 100;
 *   b = a + MOD;
 *   // istreamとostreamをオーバロードしてるので、mint型も普通に入出力できる
 *   cout << b << endl;  // 100
 *   // 明示的にlong long型を出力するときは.xを参照する
 *   cout << b.x << endl;  // 100
 *
 * References
 *  https://youtu.be/L8grWxBlIZ4?t=9858
 *  https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
 *  https://youtu.be/8uowVvQ_-Mo?t=1329 : division
 */
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
    bool operator<=(const mint a) const { return mint(*this) <= a; }
    bool operator<(const mint a) const { return mint(*this) < a; }
    bool operator>=(const mint a) const { return mint(*this) >= a; }
    bool operator>(const mint a) const { return mint(*this) > a; }
    bool operator==(const mint a) const { return mint(*this) == a; }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][s] := i人目の子供まで見て、それまでに配った飴の個数がsのときの場合の数
    vector dp(N, vector<mint>(K+1, 0));
    for(ll s=0; s<=A[0]; s++) dp[0][s] = mint(1);
    // dp更新
    for(ll i=1; i<N; i++) {
        for(ll s=0; s<=K; s++) {
            for(ll a=0; a<=A[i]; a++) { // 今回の子供にあげる飴の個数
                ll olds = s-a;
                if (olds < 0) break;
                dp[i][s] += dp[i-1][olds]; // (★)ここは dp[i-1][s] ~ dp[i-1][s-A[i]] の区間和なので、累積和で高速化できる
            }
        }
    }

    // 答え
    cout << dp[N-1][K] << endl;
}


void solve2() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][s] := i人目の子供まで見て、それまでに配った飴の個数がsのときの場合の数
    vector<mint> dp(K+1, 0); // in-place化
    for(ll s=0; s<=A[0]; s++) dp[s] = mint(1);
    // dp更新
    for(ll i=1; i<N; i++) {
        vector<mint> newdp(K+1, 0);

        // dpsum[s+1] := dp[s]までの累積和
        vector<mint> dpsum(K+2, 0);
        for(ll s=0; s<=K; s++) dpsum[s+1] = dpsum[s] + dp[s];

        // newdp更新
        for(ll s=0; s<=K; s++) {
            // (★) dp[s] ~ dp[s-A[i]] の区間和を一気に足す
            ll r = s+1;
            ll l = max(0LL, s+1-A[i]-1LL);
            newdp[s] += dpsum[r] - dpsum[l];
        }
        swap(newdp, dp);
    }

    // 答え
    cout << dp[K] << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}