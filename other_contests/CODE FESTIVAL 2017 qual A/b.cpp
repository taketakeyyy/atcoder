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
    /***
     * 左上と右下が、白の長方形
     * 左下と右上が、黒の長方形
     * の縞々模様なら作れるので、作れる黒の数を全列挙する
     * */
    ll N, M, K;
    cin >> N >> M >> K;
    set<ll> sets;
    sets.insert(0);
    sets.insert(N*M);
    for (ll i=1; i<=N; i++) {
        for(ll j=1; j<=M; j++) {
            ll total = 0;
            total += i*j;
            total += (N-i)*(M-j);
            sets.insert(total);
        }
    }

    if (sets.count(K)) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}