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


map<ll,ll> prime_factor(ll n) {
    // nを素因数分解する
    // O(√n)
    map<ll,ll> res;
    for(ll i=2; i*i<=n; i++) {
        while(n%i==0) {
            res[i]++;
            n /= i;
        }
    }

    if (n != 1) res[n]++;
    return res;
}

void solve() {
    ll N; cin >> N;

    map<ll,ll> c;  // key: 素因数分解の肩をMOD 2したときの積（f(x)）, val: その個数
    for(ll i=1; i<=N; i++) {
        map<ll,ll> pf = prime_factor(i);
        ll v = 1;
        for(auto[key, val]: pf) {
            val %= 2;
            if (val != 0) v *= key;
        }
        c[v]++;
    }

    // 出力
    ll ans = 0;
    for(auto[key, val]: c) {
        ans += val*val;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}