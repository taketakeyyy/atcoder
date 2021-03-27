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
    rep(i,N) cin >> A[i];

    // 全探索
    ll ans = INF;
    for(ll bit=0; bit<(1<<(N-1)); bit++) {
        ll orsum = A[0];
        ll xorsum = 0;
        for(ll d=0; d<(N-1); d++) {
            if (bit>>d&1) {
                // d桁目が立っていたら
                xorsum ^= orsum;
                orsum = A[d+1];
            }
            else {
                // d桁目が立っていなかったら
                orsum |= A[d+1];
            }
        }
        xorsum ^= orsum;
        ans = min(ans, xorsum);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}