#include <iostream>
#include <string>
using namespace std;

int main(void){
    string s;
    cin >> s;
    if(s[0]==s[1] && s[0]==s[2] ||
       s[3]==s[2] && s[3]==s[1]){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    
    return 0;
}