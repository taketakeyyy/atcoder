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
    ll N, K; cin >> N >> K;
    // 「整数列AとBの各要素の差の合計」とKの差が、偶数ならOK
    vector<ll> A(N), B(N);
    for(int i=0; i<N; i++) cin >> A[i];
    for(int i=0; i<N; i++) cin >> B[i];
    ll total = 0;
    for(int i=0; i<N; i++) {
        total += abs(A[i]-B[i]);
    }

    if (K>=total && ((K-total)%2)==0) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}