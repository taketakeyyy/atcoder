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
    vector<int> data(5);
    for (int i=0; i<data.size(); i++)
    {
        cin >> data.at(i);
    }

    int pre_x = data.at(0);
    for (int i=1; i<data.size(); i++)
    {
        if (data.at(i) == pre_x)
        {
            cout << "YES" << endl;
            return;
        }

        pre_x = data.at(i);
    }
    cout << "NO" << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}