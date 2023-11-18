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

bool is_zoro(ll n, ll a) {
    bool is_ok = true;
    while(n != 0) {
        if (a == n%10) {
            n /= 10;
            continue;
        }
        is_ok = false;
        break;
    }
    return is_ok;
}

void solve() {
    ll N; cin >> N;
    vector<ll> D(N);
    for(ll i=0; i<N; i++) {
        cin >> D[i];
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        for(ll j=1; j<=D[i]; j++) {
            ll a = (i+1)%10; // aのゾロ目か？

            // iがゾロ目か？
            if (!is_zoro(i+1, a)) continue;

            // jがゾロ目か？
            if (!is_zoro(j, a)) continue;
            ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}