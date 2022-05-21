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
    vector<ll> A(N), B(N);
    ll maxA = -1;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        maxA = max(maxA, A[i]);
    }
    for(ll i=0; i<K; i++) {
        cin >> B[i];
    }

    set<ll> setidx;
    for(ll i=0; i<N; i++) {
        if (maxA == A[i]) {
            setidx.insert(i+1);
        }
    }

    for(ll i=0; i<K; i++) {
        if (setidx.count(B[i])) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}