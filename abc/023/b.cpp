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
    int N;
    string s;
    cin >> N;
    cin >> s;

    string now = "b";

    if(s == now){
        printf("0\n");
        return 0;
    }

    int i = 1;
    while(true){
        if(now.size() > N){
            break;
        }

        if(i%3 == 1){
            now = "a" + now + "c";
        }
        else if(i%3 == 2){
            now = "c" + now + "a";
        }
        else{
            now = "b" + now + "b";
        }

        if(now == s){
            printf("%d\n", i);
            return 0;
        }

        i++;
    }

    printf("-1\n");
    return 0;
}