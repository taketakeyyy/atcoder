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

string replace_with_str(string str, string str_from, string str_to) {
    string::size_type pos = 0;
    while (pos = str.find(str_from, pos), pos != string::npos) {
        str.replace(pos, str_from.length(), str_to);
        pos += str_to.length();
    }
    return str;
}

void solve(){
    string S;
    string T;
    cin >> S >> T;

    int ans = 0;
    for(int i=0; i<S.size(); i++) {
        if (S[i] != T[i]) ans++;
    }

    cout << ans << endl;
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}