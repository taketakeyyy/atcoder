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
    vector<string> normal(N);
    vector<string> speed(M);
    set<string> speed_set;
    for (ll i=0; i<N; i++) {
        cin >> normal[i];
    }
    for (ll i=0; i<M; i++) {
        cin >> speed[i];
        speed_set.insert(speed[i]);
    }

    for(ll i=0; i<N; i++) {
        if (speed_set.count(normal[i])) {
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