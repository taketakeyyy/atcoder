#include <iostream>
#include <string>
using namespace std;

int main(void){
    string s;
    cin >> s;
    
    // implements
    s[3] = '8';
    printf("%s\n", s.c_str());
}