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
    ll N, K; cin >> N >> K;
    vector P(N, vector<ll>(3));
    vector<ll> Total(N);
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<3; j++) {
            cin >> P[i][j];
            Total[i] += P[i][j];
        }
    }

    vector<ll> Ranking = Total;
    sort(Ranking.begin(), Ranking.end());

    for(ll i=0; i<N; i++) {
        ll total = Total[i]+300;
        ll idx = upper_bound(Ranking.begin(), Ranking.end(), total) - Ranking.begin();
        if (N-idx+1 <= K) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }

}


int main() {
    solve();
    return 0;
}