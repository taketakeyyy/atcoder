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
    ll N, K; cin >> N >> K;
    vector<ll> C(N);
    for(ll i=0; i<N; i++) {
        cin >> C[i];
    }

    // 尺取法
    map<ll,ll> mp;
    set<ll> kind;
    for(ll i=0; i<K; i++) {
        kind.insert(C[i]);
        mp[C[i]]++;
    }

    ll ans = kind.size();
    for(ll i=K; i<N; i++) {
        mp[C[i-K]]--;
        if (mp[C[i-K]] == 0) {
            kind.erase(C[i-K]);
        }
        mp[C[i]]++;
        kind.insert(C[i]);

        ans = max(ans, (ll)kind.size());
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}