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
    vector<int> Ts(N);
    for (int i=0; i<N; i++) {
        cin >> Ts.at(i);
    }

    sort(Ts.begin(), Ts.end());
    reverse(Ts.begin(), Ts.end());

    int a=0;
    int b=0;
    for (int i=0; i<N; i++) {
        if (a == b) {
            a += Ts.at(i);
        }
        else if (a > b) {
            b += Ts.at(i);
        }
        else {
            a += Ts.at(i);
        }
    }

    cout << max(a, b) << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}