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
    if(N == 1 || N == 2){
        cout << "0\n";
        return 0;
    }

    if(N == 3){
        cout << "1\n";
        return 0;
    }

    vector<long long int> v(N+1, 0);
    v[1] = 0;
    v[2] = 0;
    v[3] = 1;
    for(int i=4; i<=N; i++){
        v[i] = (v[i-1]+v[i-2]+v[i-3])%10007;
    }

    cout << v[N]%10007 << endl;
    return 0;
}