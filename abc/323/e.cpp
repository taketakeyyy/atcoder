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
    ll N, X; cin >> N >> X;
    vector<ll> T(N);
    for(ll i=0; i<N; i++) cin >> T[i];

    deque<pair<ll,mint>> deq; // (時刻、確率)
    deq.push_back({0,mint(1)});
    mint ans = 0;
    while(!deq.empty()) {
        auto[t, p] = deq.front(); deq.pop_front();
        for(ll i=0; i<N; i++) {
            if (t+T[i] <= X) {
                deq.push_back({t+T[i], p/mint(N)});
            }
            else {
                if (i == 0) {
                    ans += p/mint(N);
                }
            }
        }
    }
    cout << ans << endl;
}


// 解説AC
void solve2() {
    ll N, X; cin >> N >> X;
    vector<ll> T(N);
    for(ll i=0; i<N; i++) cin >> T[i];

    // P[t] := 時刻tに曲が切り替わる確率
    mint ans = 0;
    vector<mint> P(X+1);
    P[0] = 1;
    if (T[0] > X) ans += P[0]/(mint(N));
    for(ll i=1; i<=X; i++) {
        for(ll j=0; j<N; j++) {
            if (T[j] <= i) {
                P[i] += P[i-T[j]];
            }
        }
        P[i] /= mint(N);
        if (i + T[0] > X) ans += P[i]/mint(N);
    }
    cout << ans << endl;
}

// AC
void solve3() {
    ll N, X; cin >> N >> X;
    vector<ll> T(N);
    for(ll i=0; i<N; i++) cin >> T[i];

    // dp[t] := 時刻tから曲が流れ始める確率（時刻tに曲が切り替わる確率）
    mint ans = 0;
    mint p = mint(1)/mint(N); // 等確率
    vector<mint> dp(X+1, 0);
    dp[0] = 1;
    for(ll t=0; t<=X; t++) { // 時刻t
        for(ll i=0; i<N; i++) { // 曲i
            if (t+T[i] <= X) dp[t+T[i]] += dp[t]*p;
            else {
                if (i == 0) ans += dp[t]*p; // 曲0は時刻X+0.5に流れている
            }
        }
    }

    // 答え
    cout << ans << endl;
}

int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}