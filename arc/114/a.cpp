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

set<ll> prime_factor_ver_set(ll n) {
    set<ll> ans;
    if (n <= 1) return ans;

    for (ll i=2; i*i<=n; i++) {
        while (n%i == 0) {
            ans.insert(i);
            n /= i;
        }
    }

    if (n != 1) ans.insert(n);

    return ans;
}

void solve() {
    ll N; cin >> N;
    vector<ll>X(N);
    rep(i,N) cin >> X[i];
    sort(X.begin(), X.end());

    set<ll> coprime_sets;
    for (int i=0; i<N; i++) {
        set<ll>s = prime_factor_ver_set(X[i]);
        for(ll a: s) {
            if (a==1) continue;
            coprime_sets.insert(a);
        }
    }

    vector<ll> coprimes;
    for(ll a: coprime_sets) {
        coprimes.push_back(a);
    }

    // 素因数の集合に対して、全探索をする
    ll ans = INF;
    ll NN = coprimes.size();
    for(ll bit=0; bit<(1<<NN); bit++) {
        ll now = 1;
        for(ll d=0; d<NN; d++) {
            if (bit>>d&1) {
                now *= coprimes[d];
            }
        }

        bool is_found = false;  // 互いに素かどうか
        for(ll x: X) {
            if (gcd(now, x)==1) {
                is_found = true;
                break;
            }
        }

        if (!is_found) {
            ans = min(ans, now);
        }
    }

    cout << ans << endl;
}



int main() {
    solve();
    return 0;
}