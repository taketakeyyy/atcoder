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
    int D, T, S;
    cin >> D >> T >> S;
    if ((double)D/S > T) {
        cout << "No" << endl;
    }
    else {
        cout << "Yes" << endl;
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}