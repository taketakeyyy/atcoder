#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
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


/*
正整数nを素因数分解して、因数をkey、指数部をvalueとしたmapを返す関数
*/
template <typename T>
map<T, T> prime_factor_ver_map(T n) {
    map<T, T> ans;
    if (n <= 1) return ans;

    for (T i=2; i*i<=n; i++) {
        while (n%i == 0) {
            ans[i]++;
            n /= i;
        }
    }

    if (n != 1) ans[n]++;

    return ans;
}


void solve() {
    ll N; cin >> N;
    map<ll,ll> pmap = prime_factor_ver_map<ll>(N);

    // 素因数の個数を数える
    ll cnt = 0;
    for(auto[key, val]: pmap) {
        cnt += val;
    }

    // 2^x >= cnt となる最小のxを探す
    ll x = 0;
    ll a = 1;
    while(1) {
        if (a >= cnt) break;
        a *= 2;
        x++;
    }
    cout << x << endl;
}


int main() {
    solve();
    return 0;
}