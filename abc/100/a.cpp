#include <iostream>
#include <string>
using namespace std;

int main(void){
    int A, B;
    string ans;
    scanf("%d %d",&A, &B);
    // implements
    if(A <= 8 && B <= 8){
        ans = "Yay!";
    }
    else{
        ans = ":(";
    }
    // output
    printf("%s\n", ans.c_str());
}