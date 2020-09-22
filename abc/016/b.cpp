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

int main(int argc, char const *argv[]){
    int A, B, C;
    cin >> A >> B >> C;
    bool is_plus = false, is_minus = false;
    if(A+B == C){
        is_plus = true;
    }
    if(A-B == C){
        is_minus = true;
    }

    if(is_plus && is_minus){
        cout << "?\n";
    }
    else if(!is_plus && is_minus){
        cout << "-\n";
    }
    else if(is_plus && !is_minus){
        cout << "+\n";
    }
    else{
        cout << "!\n";
    }
    return 0;
}