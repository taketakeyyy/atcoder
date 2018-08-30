#include <iostream>
#include <string>
using namespace std;

int main(void){
    string s;
    cin >> s;
    if(s == "100" || s == "010" || s == "001"){
        printf("1\n");
    }
    else if(s == "110" || s == "101" || s == "011"){
        printf("2\n");
    }
    else if(s == "111"){
        printf("3\n");
    }
    else{
        printf("0\n");
    }
    return 0;
}