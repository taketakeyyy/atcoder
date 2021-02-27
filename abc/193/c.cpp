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
    if (N==1) {
        cout << 1 << endl;
        return;
    }
    set<ll> sets;  // 表せれるやつの集合
    for (ll i=2; i*i<=N; i++) {
        for(ll j=i*i; j<=N; j*=i) {
            sets.insert(j);
        }
    }
    cout << N - sets.size() << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}