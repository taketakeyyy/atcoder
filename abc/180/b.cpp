#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <iomanip>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;


void solve(){
    int N;
    cin >> N;

    long long ans1 = 0;  // マンハッタン距離
    double ans2 = 0;  // ユークリッド距離
    int ans3 = 0;  // チェビシェフ距離
    for (int i=0; i<N; i++) {
        int x;
        cin >> x;
        ans1 += abs(x);
        ans2 += pow(x,2);
        ans3 = max(ans3, abs(x));
    }
    ans2 = pow(ans2, 0.5);

    cout << ans1 << endl;
    cout << fixed << setprecision(10) << ans2 << endl;
    cout << ans3 << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}