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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // nC2
    auto combo = [](ll n) -> ll {
        return (n*(n-1))/2LL;
    };

    ll ans = 0;
    ll l = 0;
    while(1) {
        if (l+1 >= N) break;
        ll d = A[l+1]-A[l];
        ll r;
        for(ll i=l+1; i<N; i++) {
            if (A[i]-A[i-1] == d) {
                r = i;
                continue;
            }
            else {
                break;
            }
        }

        if (r-l >= 2) {
            // まとめて足す
            ll total = combo(r-l+1);
            total -= (r-l);
            ans += total;
        }
        l = r;
    }

    // 長さ1のもの
    ans += N;
    // 長さ2のもの
    ans += (N-1);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}