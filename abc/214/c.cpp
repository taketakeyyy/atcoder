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
    ll N; cin >> N;
    vector<ll> S(N), T(N);
    for(ll i=0; i<N; i++) cin >> S[i];
    for(ll i=0; i<N; i++) cin >> T[i];

    // dp[k] := k番目の人が最初に宝石を受け取る時刻
    vector<ll> dp(N, -1);
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    for(ll i=0; i<N; i++) {
        pq.push({T[i], i});
    }

    while(!pq.empty()) {
        ll t, id;
        tie(t, id) = pq.top();
        pq.pop();

        if (dp[id] == -1) {
            dp[id] = t;
            pq.push({t+S[id], (id+1)%N});
        }
    }

    for(ll i=0; i<N; i++) {
        cout << dp[i] << endl;
    }
}


int main() {
    solve();
    return 0;
}