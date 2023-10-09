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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
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


// ・選ぶサイコロは必ず10個以下（出目は最低1なので）
// ・ちょうど10が作れるかが問題なので、10以下の出目について関心がある
// ・「サイコロを同時に振る」→「サイコロを1個ずつ振っていく」でもOK
// dp[i][j] := i番目のサイコロを振り終わった時点で、作れる出目の総和がjである確率
// これ、選ばなかったサイコロの状態も場合の数に関係してくるのでWAになります。
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<mint> P(N); // i番目のサイコロの等確率
    for(ll i=0; i<N; i++) P[i] = mint(1)/mint(A[i]);

    // dp[i][j] := i番目のサイコロを振り終わった時点で、作れる出目の総和がjである確率
    vector<mint> dp(11);
    dp[0] = 1;
    for(ll i=0; i<N; i++) {
        auto olddp = dp;
        // サイコロを選ばない場合、前回の値そのまま
        // サイコロを選ぶ場合
        for(ll j=0; j<11; j++) { // 総和j
            for(ll a=1; a<=min(10LL, A[i]); a++) { // サイコロiの出目
                if (j+a <= 10) dp[j+a] += olddp[j] * P[i];
            }
        }
    }

    // 答え
    cout << dp[10] << endl;
}


// 解説AC 部分和問題
// dp[i][S]=i番目のサイコロまで振った時、0から10のうち作れるものの集合がSになる確率
// Nは高々100, Sは高々2^11 = 2048通りなので、O(N 2^11)のbitDPで解ける
void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<mint> P(N); // i番目のサイコロの等確率
    for(ll i=0; i<N; i++) P[i] = mint(1)/mint(A[i]);

    const ll M = 10;
    const ll M2 = 1<<(M+1);

    // dp[i][S]=i番目のサイコロまで振った時、0から10のうち作れるものの集合がSになる確率
    vector<mint> dp(M2);
    dp[1] = 1;
    for(ll i=0; i<N; i++) {
        vector<mint> newdp(M2);

        for(ll state=0; state<M2; state++) {
            // 10以下の出目が出る場合
            for(ll a=1; a<=min(M, A[i]); a++) { // 出目がa
                ll nstate = (state|state<<a) & (M2-1); // 選ぶ場合と選ばない場合の和集合
                newdp[nstate] += dp[state]*P[i];
            }
            // 10を超える出目が出る場合
            newdp[state] += dp[state]*P[i]*max(0LL, A[i]-M); // 選ばない
        }
        dp = newdp;
    }

    // 答え
    mint ans = 0;
    for(ll state=0; state<M2; state++) {
        if (state>>M&1) ans += dp[state]; // 10を作れる集合だけ足していく
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}