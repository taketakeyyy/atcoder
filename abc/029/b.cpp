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
    int ans = 0;
    for(int i=0; i<12; i++){
        string s;
        cin >> s;
        string::size_type pos = s.find("r", 0);
        if(pos != string::npos){
            ans ++;
        }
    }
    cout << ans << "\n";
    return 0;
}