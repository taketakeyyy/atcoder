#include <iostream>
using namespace std;

int main(void){
    float R, G;
    float X;
    cin >> R;
    cin >> G;

    // implements
    X = (G-R)*2;
    printf("%f\n", X+R);
    return 0;
}
