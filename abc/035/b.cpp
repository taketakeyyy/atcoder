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
    int t;
    cin >> s;
    cin >> t;
    int ans = 0, x = 0, y = 0;
    int sum_question = 0;
    for(int i=0; i<s.size(); i++){
        if(s[i] == 'L'){
            x--;
        }
        else if(s[i] == 'R'){
            x++;
        }
        else if(s[i] == 'U'){
            y++;
        }
        else if(s[i] == 'D'){
            y--;
        }
        else{
            sum_question++;
        }
    }

    if(t == 1){
        ans += abs(x) + abs(y) + sum_question;
    }
    else{
        ans = abs(x) + abs(y);
        if(ans >= sum_question){
            ans -= sum_question;
        }
        else{
            ans = sum_question - ans;
            ans = ans % 2;
        }
    }
    printf("%d\n",ans);
    return 0;
}