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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 解説AC
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());
    ll ans = -1;
    { //パターン1 P[1] ≧ P[2] ≦ P[3] ≧ ...
        vector<ll> small(N/2);
        for(ll i=0; i<N/2; i++) small[i] = A[i];
        reverse(small.begin(), small.end());
        vector<ll> big(N - N/2);
        for(ll i=N/2; i<N; i++) big[i-N/2] = A[i];

        ll total = 0;
        // 大きい値を足していく
        ll bi = 0;
        if (N%2 == 0) {
            total += big[bi++];
        }
        else {
            total += big[bi++];
            total += big[bi++];
        }
        while(bi != (ll)big.size()) {
            total += 2*big[bi++];
        }
        // 小さい値を引いていく
        ll si = 0;
        if (N%2 == 0) {
            total -= small[si++];
        }
        while(si != (ll)small.size()) {
            total -= 2*small[si++];
        }
        ans = max(ans, total);
    }

    reverse(A.begin(), A.end());
    { // パターン2 P[1] ≦ P[2] ≧ P[3] ≦ ...
        vector<ll> big(N/2);
        for(ll i=0; i<N/2; i++) big[i] = A[i];
        sort(big.begin(), big.end());
        vector<ll> small(N - N/2);
        for(ll i=N/2; i<N; i++) small[i-N/2] = A[i];
        sort(small.begin(), small.end());
        reverse(small.begin(), small.end());

        ll total = 0;
        // 大きい値を足していく
        ll bi = 0;
        if (N%2 == 0) {
            total += big[bi++];
        }
        while(bi != (ll)big.size()) {
            total += 2*big[bi++];
        }
        // 小さい値を引いていく
        ll si = 0;
        if (N%2 == 0) {
            total -= small[si++];
        }
        else {
            total -= small[si++];
            total -= small[si++];
        }
        while(si != (ll)small.size()) {
            total -= 2*small[si++];
        }
        ans = max(ans, total);
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}