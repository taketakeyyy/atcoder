#include <iostream>
using namespace std;

int main(void){
    int x, a, b;
    cin >> x >> a >> b;

    // implements
    if(abs(x-a) <= abs(x-b)){
        printf("A\n");
    }
    else{
        printf("B\n");
    }
    return 0;
}
