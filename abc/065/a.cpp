#include <iostream>
using namespace std;

int main(void){
    int X, A, B;
    cin >> X >> A >> B;
    // implements
    if(B <= A){
        printf("delicious\n");
    }
    else if(B > (A+X)){
        printf("dangerous\n");
    }
    else{
        printf("safe\n");
    }

    return 0;
}
