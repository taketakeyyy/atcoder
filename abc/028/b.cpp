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
    map<string, int> mp;
    mp["A"] = 0;
    mp["B"] = 0;
    mp["C"] = 0;
    mp["D"] = 0;
    mp["E"] = 0;
    mp["F"] = 0;

    for(int i=0; i<s.size(); i++){
        mp[{s[i]}]++;
    }

    printf("%d %d %d %d %d %d\n", mp["A"], mp["B"], mp["C"], mp["D"], mp["E"], mp["F"]);
    return 0;
}