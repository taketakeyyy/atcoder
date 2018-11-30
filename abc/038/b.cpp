#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>

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
    int H[2], W[2];
    cin >> H[0] >> W[0];
    cin >> H[1] >> W[1];
    if(H[0] == H[1] || H[0] == W[1] || W[0] == H[1] || W[0] == W[1]){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}