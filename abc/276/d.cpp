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

// map<ll,ll> div2or3(ll x) {
//     map<ll,ll> mp;
//     while()
// }

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll g = A[0];  // 最小公約数gcd
    for(ll i=1; i<N; i++) {
        g = gcd(g, A[i]);
    }

    // 各数字はgを目指す
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        A[i] /= g;

        while(A[i]%3 == 0) {
            A[i] /= 3;
            ans++;
        }
        while(A[i]%2 == 0) {
            A[i] /=2;
            ans++;
        }

        if (A[i] != 1) {
            cout << -1 << endl;
            return;
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}