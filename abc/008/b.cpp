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
    int max_count = 0;
    string ans;
    map<string, int> mp;
    for(int i = 0; i<N; i++){
        string S;
        cin >> S;
        if(mp[S] == NULL){ mp[S] = 1; }
        else{ mp[S]++; }

        if(max_count <= mp[S]){
            max_count = mp[S];
            ans = S;
        }
    }
    cout << ans << endl;

    return 0;
}