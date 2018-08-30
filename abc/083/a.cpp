#include <iostream>
#include <string>
using namespace std;

int main(void){
    int A, B, C, D;
    string ans;
    cin >> A >> B >> C >> D;
    
    // implements
    if(A+B > C+D){
        ans = "Left";
    }
    else if(A+B < C+D){
        ans = "Right";
    }
    else{
        ans = "Balanced";
    }
    cout << ans << "\n";
}