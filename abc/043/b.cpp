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
    string s;
    cin >> s;
    string ans = "";
    int pos = 0;
    while(pos != s.size()){
        if(s[pos] != 'B'){
            ans.push_back(s[pos]);
        }
        else{
            if(ans != ""){
                ans.pop_back();
            }
        }
        pos++;
    }
    cout << ans;
    return 0;
}