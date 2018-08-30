#include <iostream>
using namespace std;
int main(void){
    int N;
    int ans;
    scanf("%d", &N);
    
    if(N%2 == 0){
        ans = N;
    }
    else{
        ans = N*2;
    }
    
    printf("%d\n", ans);
}