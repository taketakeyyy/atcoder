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
    vector<int> Ds(N);
    for (int i=0; i<N; i++)
    {
        cin >> Ds.at(i);
    }

    sort(Ds.begin(), Ds.end());
    reverse(Ds.begin(), Ds.end());

    int ans = 1;
    int pre_d = Ds.at(0);
    for (int i=1; i<N; i++)
    {
        if (Ds.at(i) < pre_d)
        {
            ans ++;
            pre_d = Ds.at(i);
        }
    }

    cout << ans << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}