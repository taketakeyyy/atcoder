#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    unsigned long long X, Y, A, B;
    cin >> X >> Y >> A >> B;

    unsigned long long ans = 0;
    while (1) {
        if (X >= Y) {
            ans--;
            break;
        }

        if ((X*(A-1)) < B) {
            X *= A; ans++;
            continue;
        }
        ans += (Y-X)/B;
        if ((Y-X)%B == 0) ans--;
        break;
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}