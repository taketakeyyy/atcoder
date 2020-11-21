#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    ll S, P; cin >> S >> P;
    for (ll N=1LL; N*N<=P; N++) {
        if (P%N!=0) continue;
        ll M = P/N;
        if (N+M == S) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}