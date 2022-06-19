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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> S(N-1);
    for(ll i=0; i<N-1; i++) {
        cin >> S[i];
    }
    vector<ll> X(M);
    for(ll i=0; i<M; i++) {
        cin >> X[i];
    }

    vector<pair<ll,ll>> A(N);  // {a, 1 or -1}
    A[0] = {0, 1};
    map<ll,ll> mp;
    for(ll i=0; i<N; i++) {
        ll a = A[i].first;
        ll c = A[i].second;
        for(ll j=0; j<M; j++) {
            ll x = X[j] - a;
            x *= c;
            mp[x]++;
        }
        if (i == N-1) break;
        A[i+1] = {S[i]-a, -A[i].second};
    }

    // 最も多いのを探す
    ll ans = 0;
    for(auto [key, val]: mp) {
        ans = max(ans, val);
    }
    cout << ans << endl;

    // map<ll,ll> cnt;
    // ll a = 0; ll c = 1;
    // for(ll i=0; i<N; i++) {
    //     for(ll j=0; j<M; j++) {
    //         ll xx = X[j] - a;
    //         cnt[xx*c]++;
    //     }
    //     if (i == N-1) break;
    //     a = S[i] - a;
    //     c = -c;
    // }
    // ll ans = 0;
    // for(auto [key, val]: cnt) {
    //     ans = max(ans, val);
    // }
    // cout << ans << endl;

}


int main() {
    solve();
    return 0;
}