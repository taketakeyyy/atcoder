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
    ll N; cin >> N;
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }

    ll ans = INF;
    for(ll target=0; target<10; target++) {
        ll maxt = -1;
        for(ll j=0; j<10; j++) {
            ll cnt = 0;
            for(ll i=0; i<N; i++) {
                if (S[i][j]-'0' == target) {
                    maxt = max(maxt, j + cnt*10);
                    cnt++;
                }
            }
        }
        ans = min(ans, maxt);
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}