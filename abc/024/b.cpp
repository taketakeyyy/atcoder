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
    int N, T;
    cin >> N >> T;
    int ans = 0;

    vector<int> A(N, 0);
    for(int i = 0; i<N; i++){
        cin >> A[i];
    }

    for(int i=0; i<N-1; i++){
        if(A[i]+T > A[i+1]){
            ans += A[i+1] - A[i];
        }
        else{
            ans += T;
        }
    }
    ans += T;

    cout << ans << endl;

    return 0;
}