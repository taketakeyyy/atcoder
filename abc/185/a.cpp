#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    vector<int> A(4);
    cin >> A[0] >> A[1] >> A[2] >> A[3];
    int ans = 0;
    ans = min(A[0], min(A[1], min(A[2], A[3])));
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}