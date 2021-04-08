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
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    map<ll,ll> mp;  // 頻度を保持する
    mp[0] = 3;
    ll ans = 1;
    for(int i=0; i<N; i++) {
        if (mp[A[i]] >= 0) {
            ans *= mp[A[i]];
            ans %= MOD;
            mp[A[i]]--;
            mp[A[i]+1]++;
            continue;
        }
        cout << 0 << endl;
        return;
    }
    cout << ans << endl;
    return;
}


int main() {
    solve();
    return 0;
}