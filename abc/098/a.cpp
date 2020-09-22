#include <iostream>
#include <algorithm>
using namespace std;

int main(void){
    int A, B;
    scanf("%d %d", &A, &B);
    
    // implements & output
    printf("%d\n", max({A*B, A-B, A+B}));
}