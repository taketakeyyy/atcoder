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
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    vector<ll> ruiseki(N+1, 0);
    for(ll i=0; i<N; i++) {
        ruiseki[i+1] = ruiseki[i] + A[i];
    }

    // にぶたん + 累積和
    for(ll q=0; q<Q; q++) {
        ll x; cin >> x;

        ll idx = lower_bound(A.begin(), A.end(), x) - A.begin();

        ll ans = 0;
        ans = ruiseki[N] - ruiseki[idx] - (N-idx)*x;
        ans += idx*x - ruiseki[idx];
        cout << ans << endl;
        // 場合分けしなくてもよさそう。にぶたんの添字むずかしい・・・
        // if (idx == 0) {
        //     ans = ruiseki[N] - x*N;
        //     cout << ans << endl;
        //     continue;
        // }
        // else if (idx == N) {
        //     ans = N*x - ruiseki[N];
        //     cout << ans << endl;
        //     continue;
        // }
        // else {
        //     ans = ruiseki[N] - ruiseki[idx] - (N-idx)*x;
        //     ans += idx*x - ruiseki[idx];
        //     cout << ans << endl;
        //     continue;
        // }
    }
}


int main() {
    solve();
    return 0;
}