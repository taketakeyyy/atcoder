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
    const int64_t WANT = 2000000000000;
    int64_t A;
    int64_t K;
    cin >> A >> K;

    if (K == 0) {
        cout << WANT-A << endl;
        return;
    }

    int64_t ans = 0;
    while (A < WANT) {
        ans ++;
        A += 1+K*A;
    }

    cout << ans << endl;

}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}