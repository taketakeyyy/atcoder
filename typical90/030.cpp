#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
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

/***素因数の種類数列挙
 * 1以上N以下の各整数の素因数の種類数を計算する
 *
 * Args:
 *  N(T): 1以上N以下の整数
 * Notes:
 *  計算量はO(NloglogN)
 **/
template <typename T>
vector<T> prime_factor_number_of_types(T N) {
    vector<T> C(N+1, 0);
    for(T i=2; i<=N; i++) {
        if (C[i] != 0) continue;  // これで素数判定をしている
        for(T j=i; j<=N; j+=i) C[j]++;
    }
    return C;
}


void solve() {
    ll N, K; cin >> N >> K;

    // 素因数列挙
    vector<ll>types = prime_factor_number_of_types<ll>(N);

    // 素因数がK以上のものを数える
    ll ans = 0;
    for(ll i=2; i<=N; i++) {
        if (types[i] >= K) ans++;
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}