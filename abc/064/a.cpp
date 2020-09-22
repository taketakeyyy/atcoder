#include <iostream>
using namespace std;

int main(void){
    int r, g, b;
    cin >> r >> g >> b;

    // implements
    if((r*100+g*10+b)%4 == 0){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }

    return 0;
}
