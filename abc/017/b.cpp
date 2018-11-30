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
    string X;
    cin >> X;
    int pos = 0;
    while(pos < X.size()){
        if(pos+1 < X.size() && X[pos] == 'c' && X[pos+1] == 'h'){
            pos += 2;
            continue;
        }
        else if(X[pos] == 'o'){
            pos++;
            continue;
        }
        else if(X[pos] == 'k'){
            pos++;
            continue;
        }
        else if(X[pos] == 'u'){
            pos++;
            continue;
        }
        else{
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}