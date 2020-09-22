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

void solve(){
    vector<vector<char>> vec(4, vector<char>(4));
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            char c;
            cin >> c;
            vec[i][j] = c;
        }
    }

    for(int i=3; i>=0; i--){
        for(int j=3; j>=0; j--){
            if(j != 0){
                printf("%c ", vec[i][j]);
            }
            else{
                printf("%c\n", vec[i][j]);
            }
        }
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}