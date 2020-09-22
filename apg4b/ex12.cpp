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
    string s;
    getline(cin, s);

    int ans = 1;
    for (int i=1; i<s.size(); i+=2)
    {
        if (s.at(i) == '+')
            ans ++;
        else
            ans --;
    }
    cout << ans << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}