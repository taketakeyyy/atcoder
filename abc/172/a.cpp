#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;


void solve(){
    int a;
    cin >> a;
    cout << a+pow(a,2)+pow(a,3) << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}