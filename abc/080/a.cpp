#include <iostream>
#include <algorithm>
using namespace std;

int main(void){
    int N, A, B;
    cin >> N >> A >> B;
    
    // implements
    cout << min({N*A, B}) << "\n";
    
    return 0;
}