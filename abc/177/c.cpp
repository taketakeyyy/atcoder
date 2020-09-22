#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <bitset>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;


void solve(){
    int N;
    cin >> N;
    vector<uint64_t> As(N, 0);
    vector<uint64_t> ruiseki(N+1, 0);
    for (int i=0; i<N; i++) {
        cin >> As.at(i);
        ruiseki.at(i+1) = (ruiseki.at(i) + As.at(i))%MOD;
    }

    /*
    求めたい値 =
    + A[1](A[0])
    + A[2](A[0]+A[1])
    + A[3](A[0]+A[1]+A[2])
    ...
    なので、累積和で解く
    */

    uint64_t ans = 0;
    for (int i=1; i<N; i++) {
        ans += (As.at(i) * ruiseki.at(i))%MOD;
        ans %= MOD;
    }

    cout << ans << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}