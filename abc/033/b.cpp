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
    int N;
    cin >> N;
    map<int, string> mp;
    int sum = 0, max_jinkou = 0;
    for(int i=0; i<N; i++){
        string s;
        int jinkou;
        cin >> s >> jinkou;
        mp[jinkou] = s;
        max_jinkou = max(max_jinkou, jinkou);
        sum += jinkou;
    }

    if(max_jinkou > sum/2){
        cout << mp[max_jinkou] << endl;
    }
    else{
        cout << "atcoder" << endl;
    }
    return 0;
}