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


void solve(){
    ll N; cin >> N;
    // xの末尾に何個0があるか？を数えたい
    // x=12390100000 のとき、123901 * 10 * 10 * 10 * 10 * 10 と書ける。
    // なので、末尾の0を数えるのは、かけている10の数を数えれば良い。
    // 10を因数分解すると 2 * 5 なので、
    // 5で割り切れる数を数えればいいのかもしれない。
    // Nが奇数のとき、N=15の場合、15*13*11*9*7*5*3*1のように、どう頑張っても因数に2が見つからないので10は作れない。よって末尾は0にならない
    // Nが偶数のとき、N=20の場合、20*18*16*14*12*10*8*6*4*2*1のように、因数に5があるのは20と10の2つ。因数に2があるのは山程あるから数えなくていいやろ多分。なので2が答え？
    // N=40の場合、40*38*36*...*30*...*20*...*10*...2*1のように、因数に5があるのは40,30,20,10の4つ。
    // N=50の場合、50,40,30,20,10の6個。50には5が2つある。
    // N=250の場合、250は50が3つある。200,150,100,50は5が2つある。240,230,220,210,190,...,20,10は5が1つ。
    if (N&1==1) {
        cout << 0 << endl;
        return;
    }

    ll ans = 0;
    ll bunbo=10;
    while(1) {
        if (bunbo>N) break;
        ans += N/bunbo;
        bunbo *= 5;
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}