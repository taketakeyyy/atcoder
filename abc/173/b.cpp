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
    int N;
    cin >> N;

    map<string, int> mp;
    mp["AC"] = 0;
    mp["WA"] = 0;
    mp["TLE"] = 0;
    mp["RE"] = 0;

    string S;
    for (int i=0; i<N; i++) {
        cin >> S;
        mp[S]++;
    }

    // 出力
    cout << "AC x " << mp["AC"] << endl;
    cout << "WA x " << mp["WA"] << endl;
    cout << "TLE x " << mp["TLE"] << endl;
    cout << "RE x " << mp["RE"] << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}