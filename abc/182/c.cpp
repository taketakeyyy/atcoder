#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    string N; cin >> N;

    int keta = N.size();

    const int INF = 10000000;
    int ans = INF;
    int bit_ans = 0;
    for (int bit=0; bit<pow(2,keta); bit++) {
        int erase = 0;
        int total = 0;
        for (int i=0; i<keta; i++) {
            if (bit>>i&1) {
                total += N[i] - '0';
            }
            else {
                erase++;
            }
        }
        if (total!=0 && total%3 == 0) {
            bit_ans = bit;
            ans = min(ans, erase);
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