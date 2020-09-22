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
    string w;
    cin >> w;
    int pos = 0;
    map<char, int> mp;
    while(pos != w.size()){
        if(mp[w[pos]] == NULL){
            mp[w[pos]] = 1;
            pos++;
            continue;
        }
        mp[w[pos]]++;
        pos++;
    }
    for(pair<char, int> p:mp){
        if(p.second%2 != 0){
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    return 0;
}