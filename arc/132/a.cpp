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
    vector<ll> R(N), C(N);
    for(ll i=0; i<N; i++) {
        cin >> R[i];
        R[i];
    }
    for(ll i=0; i<N; i++) {
        cin >> C[i];
        C[i];
    }
    ll Q; cin >> Q;

    // クエリ応答
    for(ll q=0; q<Q; q++) {
        ll r, c; cin >> r >> c;
        r--; c--;
        if (R[r]+C[c]<=N) {
            cout << ".";
        }
        else {
            cout << "#";
        }
    }
}


int main() {
    solve();
    return 0;
}