#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    ll N; cin >> N;
    vector<ll> As(N), Ps(N), Xs(N);
    ll ans = INF;
    for(int i=0; i<N; i++) {
        cin >> As[i] >> Ps[i] >> Xs[i];
        if (Xs[i] > As[i]) {
            // 買える
            ans = min(ans, Ps[i]);
        }
    }

    if (ans == INF) {
        cout << -1 << endl;
    }
    else {
        cout << ans << endl;
    }

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}