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
    int x, a, b;
    cin >> x >> a >> b;

    cout << ++x << endl;
    x *= (a+b);
    cout << x << endl;
    x *= x;
    cout << x << endl;
    cout << x-1 << endl;

}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}