#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void solve(){
    int N; cin >> N;

    // 式変形問題 max((xi+yi)-(xj+yj), (xi-yi)-(xj-yj))
    int max_sum = INT_MIN; int min_sum = INT_MAX;
    int max_sub = INT_MIN; int min_sub = INT_MAX;
    for (int i=0; i<N; i++) {
        int x, y;
        cin >> x >> y;
        max_sum = max(max_sum, x+y);
        min_sum = min(min_sum, x+y);
        max_sub = max(max_sub, x-y);
        min_sub = min(min_sub, x-y);
    }

    cout << max(max_sum-min_sum, max_sub-min_sub) << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}