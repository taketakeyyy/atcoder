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

string str_slice(string s, int start, int end){
    if(end > s.size()){
        end = s.size();
    }
    if(end-start <= 0){
        return "";
    }
    return s.substr(start, end-start);
}

int main(int argc, char const *argv[]){
    string A;
    cin >> A;
    if(A == "a"){
        cout << -1 << endl;
        return 0;
    }

    if(A.size() == 1){
        cout << char(A[0]-1) << endl;
        //printf("%c\n", A[0]-1);
        return 0;
    }

    cout << str_slice(A, 0, A.size()-1) << endl;   
    return 0;
}