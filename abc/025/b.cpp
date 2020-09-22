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
    int N, A, B;
    cin >> N >> A >> B;
    int ans = 0;
    for(int i=0; i<N; i++){
        string s;
        int d;
        cin >> s >> d;

        if(d < A){
            d = A;
        }
        else if(d > B){
            d = B;
        }

        if(s == "East"){
            ans += d;
        }
        else{
            ans -= d;
        }
    }

    if(ans == 0){
        printf("0\n");
    }
    else if(ans < 0){
        printf("West %d\n", abs(ans));
    }
    else{
        printf("East %d\n", ans);
    }

    return 0;
}