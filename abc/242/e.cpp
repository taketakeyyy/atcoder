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

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    a %= m;
    T res = mod_pow(a*a, n/2, m);
    if (n&1) res = (res * a) % m;
    return res;
}

void solve() {
    ll T; cin >> T;
    for(ll t=0; t<T; t++) {
        ll N; cin >> N;
        string S; cin >> S;
        ll M = intceil(S.size(), 2);
        ll ans = 0;
        for(ll i=0; i<M; i++) {
            ll m = S[i]-'A';
            ans += ((m%MOD) * mod_pow<ll>(26, (M-i-1), MOD))%MOD;
            ans %= MOD;
        }
        // 最後、真ん中の文字が一致するときは足すのかどうか？
        // 実際に作って確かめる
        string tmp = S.substr(0, M);
        if (S.size()%2 == 0) {
            for(ll i=M-1; i>=0; i--) {
                tmp += S[i];
            }
        }
        else {
            for(ll i=M-2; i>=0; i--) {
                tmp += S[i];
            }
        }
        if (tmp <= S) {
            ans += 1; ans %= MOD;
        }
        // 出力
        cout << ans << endl;
    }
}

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


void solve2() {
    ll T; cin >> T;
    vector<mint> anss(T);
    for(ll t=0; t<T; t++) {
        ll N; string S; cin >> N >> S;

        // 上位i桁目が、N未満フラグ(0 or 1)のときの、場合の数
        vector<mint> dp(2);
        dp[0] = 1;
        dp[1] = (S[0]-'A');
        string T1 = {S[0]}; // (最後までN未満フラグ0の回分を作る)
        for(ll i=1; i<intceil(N,2); i++) {
            vector<mint> newdp(2);
            ll a = S[i] - 'A';
            T1 += S[i];
            newdp[0] += dp[0];
            newdp[1] += dp[0]*a;
            newdp[1] += dp[1]*26; // A~ZどれでもOK
            dp = newdp;
        }
        anss[t] = dp[0] + dp[1];

        // コーナーケース(最後までN未満フラグ0の回分が、Sより大きかったら1個引かなければならない）
        string T2 = T1;
        if (N%2 != 0) {
            T2.pop_back();
        }
        reverse(T2.begin(), T2.end());
        string T3 = T1 + T2;
        if (T3 > S) anss[t] -= 1;
    }

    // 出力
    for(ll t=0; t<T; t++) cout << anss[t] << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}