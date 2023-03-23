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


// 解説AC
void solve() {
    ll N, D; cin >> N >> D;

    // 2べきを作る
    vector<mint> two(N+1);
    two[0] = 1;
    for(ll i=0; i<N; i++) two[i+1] = two[i]*2;

    // gを求める
    vector<mint> g(N+1);
    for(ll i=1; i<=N; i++) {
        ll l = i-1, r=D-l; // l:=上り, r:=下り の長さ
        mint leaf = 0; // 葉を使うパス
        if (0<=r && r<=i-1) {
            leaf = two[max(l-1,0LL)]*two[max(r-1,0LL)];
            if (l != r) leaf *= 2;
        }
        g[i] = g[i-1] + leaf;
    }

    // fを求める
    vector<mint> f(N+1);
    for(ll i=1; i<=N; i++) {
        f[i] = f[i-1]*2 + g[i];
    }
    cout << f[N]*2 << endl; // (1,4),(4,1)みたいに単純パスの向きがあるので2倍する
}


// 解説AC
// 距離がDの頂点の組(l,r)で、(l,r)の最近共通祖先（LCA）がvであるものの個数を数える
void solve2() {
    ll N, D; cin >> N >> D;

    // 2のべき乗
    vector<mint> pow2(max(N,D), 1); // pow2[i] := 2^i乗
    for(ll i=1; i<max(N,D); i++) pow2[i] = pow2[i-1]*2;

    // 事前に、部分木の深さがdのときの場合の数を数える
    vector<mint> f(D+1, 0); // f[d] := 部分木の深さがdのときの場合の数
    for(ll l=D; l>0; l--) {
        if (l == D) {
            f[l] += pow2[l] * 2;
        }
        else {
            ll r = D - l;
            f[max(l,r)] += pow2[l-1] * pow2[r-1] * 2;
        }
    }
    for(ll d=0; d<D; d++) f[d+1] += f[d]; // いもす法で累積和

    // LCAの深さを下に下げながら数え上げ
    mint ans = 0;
    for(ll lca=0; lca<N-1; lca++) { // LCAの深さ
        ll d = min(N-1-lca, D);
        ans += f[d] * pow2[lca];
    }
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}