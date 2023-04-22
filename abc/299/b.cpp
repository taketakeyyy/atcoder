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


void solve() {
    ll N, T; cin >> N >> T;
    vector<ll> C(N), R(N);
    for(ll i=0; i<N; i++) cin >> C[i];
    for(ll i=0; i<N; i++) cin >> R[i];

    map<ll,pair<ll,ll>> mp;
    for(ll i=0; i<N; i++) {
        ll c = C[i];
        ll r = R[i];

        if (mp.count(c)) {
            auto[v, idx] = mp[c];
            if (r > v) {
                mp[c] = {r, i};
            }
        }
        else {
            mp[c] = {r, i};
        }
    }

    if (mp.count(T)) {
        auto[v, idx] = mp[T];
        cout << idx+1 << endl;
    }
    else {
        auto[v, idx] = mp[C[0]];
        cout << idx+1 << endl;
    }
}


int main() {
    solve();
    return 0;
}