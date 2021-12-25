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
    ll N, K; cin >> N >> K;  // K=0のとき注意？
    vector<ll> A(N);
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        // if (A[i]==K) ans++;
    }

    vector<ll> ruiseki(N+1, 0);
    map<ll,ll> mapRuiseki;
    for(ll i=1; i<=N; i++) {
        ruiseki[i] = ruiseki[i-1] + A[i-1];
        mapRuiseki[ruiseki[i]]++;
        if (K != 0) {
            if (ruiseki[i]==K) ans++;
        }
        if (mapRuiseki[ruiseki[i]-K]) {
            ans += mapRuiseki[ruiseki[i]-K];
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}