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
    ll N, X; cin >> N >> X;
    X--;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        A[i]--;
    }

    set<ll> known;
    known.insert(X);
    ll i = X;
    while(1) {
        if (known.count(A[i])) {
            break;
        }
        known.insert(A[i]);
        i = A[i];
    }

    cout << known.size() << endl;
}


int main() {
    solve();
    return 0;
}