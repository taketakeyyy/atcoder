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


// 二分探索
void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    auto f = [&](ll x) -> pair<ll,ll> {
        ll plus = 0;
        ll minus = 0;
        for(ll i=0; i<N; i++) {
            if (x == A[i]) continue;
            if (x > A[i]) {
                plus += x - A[i];
            }
            else {
                minus += A[i] - x;
            }
        }

        return {plus, minus};
    };

    ll ans = INF;
    ll l = 0, r = 1e9+1;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        auto[plus, minus] = f(mid);

        if (abs(plus-minus) <= 1) {
            ans = min(ans, min(plus, minus));
        }

        if (plus-minus < 0) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    {
        auto[plus, minus] = f(l);
        if (abs(plus-minus) <= 1) {
            ans = min(ans, min(plus, minus));
        }
    }
    {
        auto[plus, minus] = f(r);
        if (abs(plus-minus) <= 1) {
            ans = min(ans, min(plus, minus));
        }
    }
    cout << ans << endl;
}


void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    ll total = 0;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        total += A[i];
    }
    ll x = total/N;

    // (x, x+1)近い方に近づける
    auto f = [&](ll x) -> pair<ll,ll> {
        ll plus = 0;
        ll minus = 0;
        for(ll i=0; i<N; i++) {
            if (A[i]==x || A[i]==x+1) continue;
            if (A[i] > x+1) {
                minus += A[i]-(x+1);
            }
            if (A[i] < x) {
                plus += x - A[i];
            }
        }
        return {plus, minus};
    };

    ll ans = INF;
    {
        auto[plus, minus] = f(x);
        ans = min(ans, max(plus, minus));
    }
    {
        auto[plus, minus] = f(x-1);
        ans = min(ans, max(plus, minus));
    }
    {
        auto[plus, minus] = f(x+1);
        ans = min(ans, max(plus, minus));
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}