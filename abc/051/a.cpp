#include <iostream>
#include <string>
#include <math.h>

using namespace std;

string replace_with_str(string s, string from, string to){
    string::size_type pos = 0;
    while(pos = s.find(from, pos), pos != string::npos){
        s.replace(pos, from.length(), to);
        pos += to.length();
    }
    return s;
}

int main(int argc, char const *argv[]){
    string s;
    cin >> s;
    s = replace_with_str(s, ",", " ");
    printf("%s\n",s.c_str());
    return 0;
}