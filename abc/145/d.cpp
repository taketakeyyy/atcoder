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

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

template <typename T>
T combination_mod(T n, T r, T mod) {
    /*** nCrを O(min(n-r, r)) で高速に計算する ***/
    auto inv = [mod](T x) { return mod_pow<T>(x, mod-2, mod); };

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i)%mod;
        bunbo = bunbo*(i+1)%mod;
    }
    return (bunsi*inv(bunbo))%mod;
}

void solve(){
    ll X, Y; cin >> X >> Y;
    // DPで解く
    // このナイトは右下方向にしか移動できない。遷移を絵に書いてみればわかるが、次元圧縮できる。
    // すると、パスカルの三角形が作れることに気づく。
    // パスカルの三角形は二項係数の表なので、Combinationの計算を求めれば良いことになる。
    if ((X+Y)%3!=0) {
        cout << 0 << endl;
        return;
    }
    ll n = (X+Y)/3;
    ll x = 2*n;
    ll y = x/2;
    bool is_ok = false;
    ll cnt = 0;
    while(cnt!=(n+1)) {
        if ((x-cnt)==X && (y+cnt)==Y) {
            is_ok = true;
            break;
        }
        cnt++;
    }
    if (!is_ok) {
        cout << 0 << endl;
        return;
    }

    ll ans = combination_mod<ll>(n, cnt, MOD);
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}