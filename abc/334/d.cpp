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
    ll N, Q; cin >> N >> Q;
    vector<ll> R(N);
    for(ll i=0; i<N; i++) cin >> R[i];
    sort(R.begin(), R.end());

    vector<ll> ruiR(N+1, 0);
    for(ll i=0; i<N; i++) {
        ruiR[i+1] = ruiR[i] + R[i];
    }

    for(ll q=0; q<Q; q++) {
        ll x; cin >> x;
        ll idx = lower_bound(ruiR.begin(), ruiR.end(), x) - ruiR.begin();
        if (ruiR[idx] == x) {
            cout << idx << endl;
        }
        else {
            cout << idx-1 << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}