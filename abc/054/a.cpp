#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, char const *argv[]){
    int a, b;
    scanf("%d %d",&a, &b);
    if(a == 1 && b == 1){
        printf("Draw\n");
        return 0;
    }
    else if(a == 1){
        printf("Alice\n");
        return 0;
    }
    else if(b == 1){
        printf("Bob\n");
        return 0;
    }

    if(a == b){
        printf("Draw\n");
        return 0;
    }
    else if(a > b){
        printf("Alice\n");
        return 0;
    }
    else{
        printf("Bob\n");
        return 0;
    }
    return 0;
}