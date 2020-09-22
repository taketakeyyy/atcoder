#include <iostream>
using namespace std;

int main(void){
    char X, Y;
    cin >> X >> Y;

    // implements
    if(X < Y){
        printf("<\n");
    }
    else if(X > Y){
        printf(">\n");
    }
    else{
        printf("=");
    }
    return 0;
}
