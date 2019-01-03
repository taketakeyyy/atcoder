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

bool is_atcoder(char c){
    if(c == 'a' || c == 't' || c == 'c' || c == 'o' || c == 'd' || c == 'e' || c == 'r'){
        return true;
    }
    return false;
}

void solve(){
    string s, t;
    cin >> s >> t;

    bool can_win = true;
    for(int i=0; i<s.size(); i++){
        if(s[i] == t[i]){
            continue;
        }
        else if(s[i] == '@' && is_atcoder(t[i])){
            continue;
        }
        else if(t[i] == '@' && is_atcoder(s[i])){
            continue;
        }
        can_win = false;
        break;
    }

    if(can_win){
        cout << "You can win\n";
    }
    else{
        cout << "You will lose\n";
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}