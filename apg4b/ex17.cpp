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
    int N, S;
    cin >> N >> S;
    vector<int> A(N), P(N);
    for (int i=0; i<N; i++) {
        cin >> A.at(i);
    }
    for (int i=0; i<N; i++) {
        cin >> P.at(i);
    }

    int ans = 0;
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            if (A.at(i)+P.at(j) == S) ans++;
        }
    }

    cout << ans << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}