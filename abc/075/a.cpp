#include <iostream>
using namespace std;

int main(void){
    int A, B, C;
    cin >> A >> B >> C;

    // implements
    if(A == B){
        printf("%d\n", C);
    }
    else if(A == C){
        printf("%d\n", B);
    }
    else{
        printf("%d\n", A);
    }
    return 0;
}
