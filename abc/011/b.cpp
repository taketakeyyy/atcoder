#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

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
    transform(s.begin(), s.begin()+1, s.begin(), ::toupper);
    transform(s.begin()+1, s.end(), s.begin()+1, ::tolower);
    cout << s << endl;
    return 0;
}