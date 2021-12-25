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

ll ans = 0;

void dfs(ll i, vector<map<ll,ll>> &mapA, ll X, ll cnt) {
    if (X==0) return;
    if (i==mapA.size() && X==1) {
        ans += cnt;
        return;
    }

    if (i < mapA.size()) {
        for(auto [a, c] : mapA[i]) {
            dfs(i+1, mapA, X/a, cnt*c);
        }
    }
}

void solve() {
    ll N, X; cin >> N >> X;
    vector<ll> L(N);
    vector<vector<ll>> A(N);
    vector<map<ll,ll>> mapA(N);
    for(ll i=0; i<N; i++) {
        cin >> L[i];
        A[i].resize(L[i]);
        for(ll l=0; l<L[i]; l++) {
            ll a; cin >> a;
            A[i][l] = a;
            if (X%a != 0) continue;
            mapA[i][a]++;
        }
    }

    dfs(0, mapA, X, 1);

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}