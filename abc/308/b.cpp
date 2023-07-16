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
    ll N, M; cin >> N >> M;
    vector<string> C(N);
    for(ll i=0; i<N; i++) cin >> C[i];
    vector<string> D(M+1);
    for(ll i=1; i<M+1; i++) cin >> D[i];
    vector<ll> P(M+1);
    cin >> P[0];
    for(ll i=1; i<M+1; i++) cin >> P[i];

    map<string, ll> mp; // 価格表
    for(ll i=1; i<M+1; i++) {
        mp[D[i]] = P[i];
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        if (mp.count(C[i])) {
            ans += mp[C[i]];
        }
        else {
            ans += P[0];
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}