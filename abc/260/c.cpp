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
    ll N, X, Y; cin >> N >> X >> Y;
    vector<ll> R(N+1,0), B(N+1,0);  // R[i] := 赤い宝石レベルiの個数
    R[N] = 1;
    for(ll i=N; i>=2; i--) {
        // 赤い宝石を変換しまくる
        if (R[i] >= 1) {
            B[i] += X * R[i];
            R[i-1] += R[i];
            R[i] = 0;
        }

        // 青い宝石を変換しまくる
        if (B[i] >= 1) {
            B[i-1] += Y * B[i];
            R[i-1] += B[i];
            B[i] = 0;
        }
    }

    cout << B[1] << endl;
}


int main() {
    solve();
    return 0;
}