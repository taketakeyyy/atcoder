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

template<typename T>
T combination(T n, T r) {
    /***nCrは、O(min(n-r, r))で実装する

    Example:
        100C98 = 100!/(98!*2!)
               = 100*99/2*1
        となることから、計算量は減らせる

    Notes:
        分子と分母がかなり大きな値になった場合、計算は遅くなるので注意
        求める値がmodをとった値でいい場合、後述のフェルマーの小定理を使った方法が速い。
    ***/
    if (n < r) return 0;

    r = min(n-r, r);
    T bunsi=1, bunbo=1;
    for (T i=0; i<r; i++) {
        bunsi = bunsi*(n-i);
        bunbo = bunbo*(i+1);
    }
    return bunsi/bunbo;
}

template<typename T>
T permutation(T n, T r) {
    T ans = 1;
    for (T i=n; i>n-r; --i) {
        ans = ans*i;
    }
    return ans;
}

void solve() {
    ll N; cin >> N;
    vector<ll> A;
    map<ll,ll> mp;
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        if (!mp.count(a)) {
            A.push_back(a);
        }
        mp[a]++;
    }

    sort(A.begin(), A.end());

    // A[i] = A[k]A[j]を探す
    const ll MAX_VAL = 200000;
    ll ans = 0;
    ll M = A.size();
    for(ll k=0; k<M; k++) {
        for(ll j=0; j<M; j++) {
            ll b = A[k];
            ll c = A[j];
            ll a = b*c;

            if (a > MAX_VAL) break;
            ans += mp[a]*mp[b]*mp[c];  // i==j==kでもOKに注意
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}