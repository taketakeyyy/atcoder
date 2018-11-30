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
    string s;
    cin >> s;

    char now = s[0];
    int num = 1;
    string ans = "";
    for(int i=1; i<s.size(); i++){
        if(now != s[i]){
            ans += now + to_string(num);
            now = {s[i]};
            num = 1;
            continue;
        }
        num++;
    }
    ans += now + to_string(num);

    cout << ans << endl;
    return 0;
}