#include <iostream>
using namespace std;

int main(void){
    int A, B, C;
    cin >> A >> B >> C;
    if(C >= A && C <= B){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    return 0;
}
