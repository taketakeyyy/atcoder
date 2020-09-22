#include <iostream>
#include <string>
using namespace std;

int main(void){
    int N;
    string ans = "ABC";
    scanf("%d", &N);
    
    // implements
    if(N >= 1000){
       ans = "ABD";
    }
    
    // output
    printf("%s\n", ans.c_str());
}