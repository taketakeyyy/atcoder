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
    int ans = 0;
    int now = 1;
    for (int i=0; i<N; i++) {
        int a;
        cin >> a;
        if (now != a) {
            ans++;
        }
        else {
            now++;
        }
    }

    if (now == 1) {
        cout << "-1" << endl;
    }
    else {
        cout << ans << endl;
    }

}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}