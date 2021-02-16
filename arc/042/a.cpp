#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    ll N, M; cin >> N >> M;
    vector<ll>As(M);
    for(ll i=0; i<M; i++) cin >> As[i];

    set<ll> visited;
    for(ll i=As.size()-1; i>=0; i--) {
        if (visited.count(As[i])) continue;
        cout << As[i] << endl;
        visited.insert(As[i]);
    }

    for (ll i=1; i<=N; i++) {
        if (visited.count(i)) continue;
        cout << i << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}