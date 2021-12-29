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


void solve() {
    ll N, M; cin >> N >> M;
    vector<pair<ll,ll>> AB(M);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        AB[i] = {a,b};
    }
    set<pair<ll,ll>> CD;
    for(ll i=0; i<M; i++) {
        ll c, d; cin >> c >> d; c--; d--;
        CD.insert({min(c,d),max(c,d)});
    }

    vector<ll> P(N);
    for(ll i=0; i<N; i++) P[i] = i;
    do {
        bool is_ok = true;
        for(auto [i,j]: AB) {
            if (CD.count({min(P[i],P[j]), max(P[i],P[j])})) continue;
            is_ok = false;
        }

        if (is_ok) {
            cout << "Yes" << endl;
            return;
        }
    }while (next_permutation(P.begin(), P.end()));
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}