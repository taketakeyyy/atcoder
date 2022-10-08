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
    ll N, M; cin >> N >> M;
    vector<set<ll>> together(N+1);
    for(ll i=1; i<=N; i++) {
        together[i].insert(i);
    }

    for(ll m=0; m<M; m++) {
        ll K; cin >> K;
        vector<ll> sanka(K);
        for(ll k=0; k<K; k++) {
            ll x; cin >> x;
            sanka[k] = x;
        }

        for(ll i=0; i<K; i++) {
            ll target = sanka[i];
            for(ll j=0; j<K; j++) {
                if (i==j) continue;
                together[target].insert(sanka[j]);
            }
        }
    }

    // 確認
    for(ll i=1; i<=N; i++) {
        if ((ll)together[i].size() != N) {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}