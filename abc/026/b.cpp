#define _USE_MATH_DEFINES  // M_PI等のフラグ

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>

#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))

using namespace std;

string replace_with_str(string str, string str_from, string str_to) {
    string::size_type pos = 0;
    while (pos = str.find(str_from, pos), pos != string::npos) {
        str.replace(pos, str_from.length(), str_to);
        pos += str_to.length();
    }
    return str;
}

int main(int argc, char const *argv[]){
    int N;
    cin >> N;
    double ans = 0.0;
    vector<int> R(N, 0);
    for(int i=0; i<N; i++){
        cin >> R[i];
    }

    stable_sort(R.begin(), R.end(), greater<int>());

    for(int i=0; i<N; i++){
        if(i%2 == 0){
            ans += R[i]*R[i];
        }
        else{
            ans -= R[i]*R[i];
        }
    }

    printf("%.15f\n", ans*M_PI);

    return 0;
}