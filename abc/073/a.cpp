#include <iostream>
#include <string>
using namespace std;

int main(void){
    string s;
    cin >> s;

    // implements
    if(s[0]=='9' || s[1]=='9'){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    return 0;
}
