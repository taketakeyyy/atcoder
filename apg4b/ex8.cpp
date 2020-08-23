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
    int i;
    cin >> i;

    if (i==1) {
        int price;
        int N;
        cin >> price;
        cin >> N;
        printf("%d\n", price*N);
    }
    else {
        string text;
        int price;
        int N;
        cin >> text >> price >> N;
        printf("%s!\n", text.c_str());
        printf("%d\n", price*N);
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}