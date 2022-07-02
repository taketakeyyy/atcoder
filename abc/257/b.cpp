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
    ll N, K, Q; cin >> N >> K >> Q;
    vector<ll> masu(N, -1);

    for(ll k=0; k<K; k++) {
        ll a; cin >> a; a--;
        masu[a] = k;
    }

    for(ll i=0; i<Q; i++) {
        ll l; cin >> l; l--;

        // 左からl番目のコマは、いまどこに？
        ll idx;
        for(ll j=0; j<N; j++) {
            if (masu[j] == l) {
                idx = j;
                break;
            }
        }

        // で、何する？
        if (idx == N-1) continue;
        if (masu[idx+1] != -1) continue;
        masu[idx+1] = masu[idx];
        masu[idx] = -1;
    }

    // 出力
    for(ll i=0; i<N; i++) {
        if (masu[i] != -1) {
            cout << i+1 << " ";
        }
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}