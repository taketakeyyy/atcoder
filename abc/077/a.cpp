#include <iostream>
#include <string>
using namespace std;

int main(void){
    string s1, s2;
    cin >> s1;
    cin >> s2;

    // implements
    if(s1[0]==s2[2] && s1[1]==s2[1] && s1[2]==s2[0]){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}
