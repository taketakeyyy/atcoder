#include <iostream>
#include <string>
using namespace std;

int main(void){
    string s;
    cin >> s;

    // implements
    if(s[0]==s[2]){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    return 0;
}
