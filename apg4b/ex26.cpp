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

    map<char, int> mp;
    for (int i=0; i<N; i++) {
        string op;
        cin >> op;
        if (op.substr(0,3) == "int") {
            char key = op.at(4);

        }
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}