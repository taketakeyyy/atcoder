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
    cin >> N;
    int ans = 0;
    for(int i=0; i<N; i++){
        int a;
        cin >> a;
        if(a == 1){
            continue;
        }
        if(a == 2){
            ans ++;
            continue;
        }

        if(a%2 == 0){
            if(a%3 == 0){
                // 30
                ans += 3;
            }
            else if(a%3 == 1){
                // 4
                ans ++;
            }
            else if(a%3 == 2){
                // 32
                ans ++;
            }
        }
        else{
            if(a%3 == 0){
                // 21
                ;
            }
            else if(a%3 == 1){
                // 19
                ;
            }
            else if(a%3 == 2){
                ans +=2;
            }
        }
    }
    cout << ans << endl;
    return 0;
}