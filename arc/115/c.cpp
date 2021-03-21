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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    vector<ll> A(N+1);
    // A[1]は1で確定
    A[1] = 1;
    ll j = 2*2;
    ll a = 2;
    for(int i=2; i<=N; i++) {
        if (i==j) {
            j = i*2;
            a++;
        }
        A[i] = a;
    }

    // 出力
    for(int i=1; i<N+1; i++) {
        cout << A[i];
        if (i!=N) cout << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}