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
    string S, T;
    cin >> S >> T;

    int ans = T.size();
    for(int i=0; i<=S.size()-T.size(); i++) {
        int ret = 0;
        for (int j=0; j<T.size(); j++) {
            if (S.at(i+j) != T.at(j)) ret ++;
        }
        ans = min(ans, ret);
    }

    cout << ans <<endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}