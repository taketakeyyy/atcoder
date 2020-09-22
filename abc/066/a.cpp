#include <iostream>
#include <algorithm>
using namespace std;

int main(void){
    int a, b, c;
    cin >>a >> b >> c;

    // implements
    printf("%d\n", min({a+b, a+c, b+c}));
    return 0;
}
