#include <iostream>
using namespace std;

int main(void){
    int A, B;
    cin >> A >> B;

    if(A+B >= 10){
        printf("error\n");
    }
    else{
        printf("%d\n", A+B);
    }
    return 0;
}
