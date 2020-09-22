#include <iostream>
using namespace std;

int main(void){
    int A, B;
    cin >> A >> B;

    // implements
    if((A+B)%3 == 0 || A%3 == 0 || B%3 == 0){
        printf("Possible\n");
    }
    else{
        printf("Impossible\n");
    }
    return 0;
}
