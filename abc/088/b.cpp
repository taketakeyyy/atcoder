#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
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
    vector<int> As(N);
    for (int i=0; i<N; i++)
    {
        cin >> As.at(i);
    }

    sort(As.begin(), As.end());
    reverse(As.begin(), As.end());

    int alice = 0;
    int bob = 0;
    for (int i=0; i<N; i++)
    {
        if (i%2 == 0)
            alice += As.at(i);
        else
            bob += As.at(i);
    }

    cout << alice - bob << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}