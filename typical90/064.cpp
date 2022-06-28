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
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> kaisa(N);  // 階差
    ll huben = 0; // 不便さ
    for(ll i=0; i<N-1; i++) {
        kaisa[i] = A[i+1] - A[i];
        huben += abs(kaisa[i]);
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll l, r, v; cin >> l >> r >> v;
        l--; r--;
        if (l-1 >= 0) {
            huben -= abs(kaisa[l-1]);
            kaisa[l-1] += v;
            huben += abs(kaisa[l-1]);
        }
        if (r <= N-2) {
            huben -= abs(kaisa[r]);
            kaisa[r] -= v;
            huben += abs(kaisa[r]);
        }
        cout << huben << endl;
    }
}


int main() {
    solve();
    return 0;
}