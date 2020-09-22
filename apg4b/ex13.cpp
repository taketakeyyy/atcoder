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
    int avg = 0;
    cin >> N;
    vector<int> As(N);
    for (int i=0; i<N; i++)
    {
        cin >> As.at(i);
        avg += As.at(i);
    }
    avg /= N;

    // どのくらい離れているのか出力する
    for (int i=0; i<N; i++)
    {
        cout << abs(avg - As.at(i)) << endl;
    }

}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}