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


int main() {
    solve();
    return 0;
}