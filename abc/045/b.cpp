#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>

#define MOD 1000000007

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
    map<char, string> s;
    cin >> s['a'];
    cin >> s['b'];
    cin >> s['c'];
    
    char next = 'a';
    while(true){
        char now = next;
        if(s[now].size() == 0){
            printf("%c\n", now + 'A'-'a');
            return 0;
        }
        next = s[now][0];
        s[now].erase(0, 1);
    }
    return 0;
}