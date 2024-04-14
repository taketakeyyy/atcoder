#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // left[i] := 区間[0,i]の累積gcd
    vector<ll> left(N);
    left[0] = A[0];
    for(ll i=1; i<N; i++) {
        left[i] = gcd(left[i-1], A[i]);
    }

    // right[i] := 区間[i,N-1]の累積gcd
    vector<ll> right(N);
    right[N-1] = A[N-1];
    for(ll i=N-2; i>=0; i--) {
        right[i] = gcd(right[i+1], A[i]);
    }

    // 各iについて、i番目の要素を消したときの最大公約数を求めて、最大のものを探す
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        if (i == 0) {
            ans = max(ans, right[1]);
        }
        else if (i == N-1) {
            ans = max(ans, left[N-2]);
        }
        else {
            ans = max(ans, gcd(left[i-1], right[i+1]));
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}