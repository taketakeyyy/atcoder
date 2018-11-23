#include <iostream>
#include <string>

using namespace std;

main(int argc, char const *argv[])
{
    char a, b;
    if(a=='H'){
        if(b=='H'){
            printf("H\n");
            return 0;
        }
        else{
            printf("D\n");
            return 0;
        }
    }
    else{
        if(b=='H'){
            printf("D\n");
            return 0;
        }
        else{
            printf("H\n");
            return 0;
        }
    }
    return 0;
}
