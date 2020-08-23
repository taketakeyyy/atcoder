#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
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
    int A, B, C;
    cin >> A >> B >> C;
    int mn, mx;
    mn = min(min(A,B),C);
    mx = max(max(A,B),C);

    cout << mx-mn << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}