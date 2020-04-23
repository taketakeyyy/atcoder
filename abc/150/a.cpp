#include <iostream>
#include <string>

using namespace std;

void solve(){
    int K, X;
    cin >> K >> X;
    if (500*K >= X) {
        printf("Yes");
    }
    else {
        printf("No");
    }
}

int main(int argc, char const *argv[]){
    solve();
    return 0;
}