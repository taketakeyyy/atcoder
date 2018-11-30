#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
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
    int k;
    cin >> s;
    cin >> k;
    if(s.size() < k){
        printf("0\n");
        return 0;
    }
    
    int ans = 0;
    map<string, bool> mp;
    for(int pos=0; pos<s.size(); pos++){
        if(pos+k > s.size()){
            break;
        }
        if(mp[s.substr(pos, k)] == NULL){
            mp[s.substr(pos, k)] = true;
            ans += 1;
        }
    }
    printf("%d\n",ans);
    return 0;
}