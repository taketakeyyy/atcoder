#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    ll A, B, K, L;
    cin >> A >> B >> K >> L;

    ll ans;
    // できるだけセットを買う場合
    ans = min((K/L)*B + (K%L)*A, (K/L+1)*B);

    // 全部バラで買う場合
    ans = min(ans, K*A);

    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}