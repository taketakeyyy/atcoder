#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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


// TLE
void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][k] := i番目まで見て、連続部分列の要素の和がkのときの、場合の数
    unordered_map<ll,mint> dp;
    dp[A[0]] = 1;
    mint total = dp[A[0]]; // dpのval和
    for(ll i=1; i<N; i++) {
        unordered_map<ll,mint> newdp;

        // 連続部分列にしない場合（ここで区切る場合）
        // for(auto[key, val]: dp) {
        //     if (key == K) continue;
        //     newdp[A[i]] += val;
        // }
        newdp[A[i]] += total-dp[K];

        // 連続部分列にする場合
        for(auto[key, val]: dp) {
            newdp[key+A[i]] += val;
            total += val;
        }

        swap(newdp, dp);
    }

    // 答え
    mint ans = 0;
    for(auto[key, val]: dp) {
        if (key == K) continue;
        ans += val;
    }
    cout << ans << endl;
}

// 解説AC
void solve2() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) cin >> A[i];

    // Aの累積和
    vector<ll> rui(N+1);
    for(ll i=1; i<=N; i++) rui[i] = rui[i-1] + A[i];

    // (j,j+1,...,i)の連続部分列を考える
    // dp[i] := 最後の分割位置がiのときの場合の数
    vector<mint> dp(N+1, 0);
    dp[0] = mint(1);
    for(ll i=1; i<=N; i++) {
        for(ll j=0; j<i; j++) { // (★)ここのループを高速化したい
            if (rui[i]-rui[j] == K) continue;
            dp[i] += dp[j]; // dp[j]の和をdp[i]に一気に足せばよさそう
        }
    }

    // 答え
    mint ans = dp[N];
    cout << ans << endl;
}


void solve3() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) cin >> A[i];

    // Aの累積和S
    vector<ll> S(N+1);
    for(ll i=1; i<=N; i++) S[i] = S[i-1] + A[i];

    // S[j] = S[i]-K であるものを数え上げる
    vector<mint> dp(N+1);
    dp[0] = 1;
    mint total = dp[0]; // 前回のdp和
    map<ll,mint> dpsum; // dpsum[S[i]] := 今までのdp[i]の合計
    dpsum[0] = 1;
    for(ll i=1; i<=N; i++) {
        // for(ll j=0; j<i; j++) dp[i] += dp[j]; // totalを足すことで不要になる
        dp[i] += total;

        // for(ll j=0; j<i; j++) {
        //     if (S[j] == S[i]-K) dp[i] -= dp[j];
        // }
        dp[i] -= dpsum[S[i]-K];

        total += dp[i];
        dpsum[S[i]] += dp[i];
    }

    // 出力
    cout << dp[N].x << endl;
}


int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}