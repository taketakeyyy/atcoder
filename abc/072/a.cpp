#include <iostream>
#include <algorithm>
using namespace std;

int main(void){
    int X, t;
    int ans;

    cin >> X >> t;
    ans = max({X-t, 0});

    printf("%d\n", ans);

    return 0;
}
